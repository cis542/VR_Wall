#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Paddle.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


GLuint theProgram_Paddle;
GLuint mouse_x_Paddle=0;
GLuint mouse_y_Paddle=0;


GLuint modelToCameraMatrixUnif_Paddle;
GLuint cameraToClipMatrixUnif_Paddle;

glm::mat4 cameraToClipMatrix_Paddle;

const int numberOfVertices_Paddle = 12;


#define OUTER_COLOR 	0.0f, 0.0f, 1.0f, 0.0f
#define INNER_COLOR     1.0f, 0.0f, 0.0f, 0.0f


const float vertexData_Paddle[] =
{
     1.5f,  1.5f, 0.0f, 1.0f,
     1.5f, -1.5f, 0.0f, 1.0f,
    -1.5f,  1.5f, 0.0f, 1.0f,

     1.5f, -1.5f, 0.0f, 1.0f,
    -1.5f, -1.5f, 0.0f, 1.0f,
    -1.5f,  1.5f, 0.0f, 1.0f,

     0.5f,  0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f,

     0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f,




   OUTER_COLOR,
   OUTER_COLOR,
   OUTER_COLOR,

   OUTER_COLOR,
   OUTER_COLOR,
   OUTER_COLOR,

   INNER_COLOR,
   INNER_COLOR,
   INNER_COLOR,

   INNER_COLOR,
   INNER_COLOR,
   INNER_COLOR,



};

const GLshort indexData_Paddle[] =
{
    0, 1, 2,
    3, 4, 5,

    6, 7, 8,
    9, 10, 11,


};

GLuint vertexBufferObject_Paddle;
GLuint indexBufferObject_Paddle;
GLuint vao_Paddle;


Paddle::Paddle()
{

}
Paddle::~Paddle()
{

}

float Paddle::CalcFrustumScalePaddle(float fFovDeg)
{
    const float degToRad = 3.14159f * 2.0f / 360.0f;
    float fFovRad = fFovDeg * degToRad;
    return 1.0f / tan(fFovRad / 2.0f);
}



void Paddle::InitializeProgramPaddle()
{
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "PosColorLocalTransform.vert"));
    shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "ColorPassthrough.frag"));

    theProgram_Paddle = Framework::CreateProgram(shaderList);

    modelToCameraMatrixUnif_Paddle = glGetUniformLocation(theProgram_Paddle, "modelToCameraMatrix");
    cameraToClipMatrixUnif_Paddle = glGetUniformLocation(theProgram_Paddle, "cameraToClipMatrix");

    float fzNear = 1.0f; float fzFar = 1000.0f;

    const float fFrustumScale_Paddle = CalcFrustumScalePaddle(45.0f);

    cameraToClipMatrix_Paddle[0].x = fFrustumScale_Paddle;
    cameraToClipMatrix_Paddle[1].y = fFrustumScale_Paddle;
    cameraToClipMatrix_Paddle[2].z = (fzFar + fzNear) / (fzNear - fzFar);
    cameraToClipMatrix_Paddle[2].w = -1.0f;
    cameraToClipMatrix_Paddle[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

    glUseProgram(theProgram_Paddle);
    glUniformMatrix4fv(cameraToClipMatrixUnif_Paddle, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix_Paddle));
    glUseProgram(0);
}




void Paddle::InitializeVertexBuffer()
{
    glGenBuffers(1, &vertexBufferObject_Paddle);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Paddle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData_Paddle), vertexData_Paddle, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &indexBufferObject_Paddle);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_Paddle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData_Paddle), indexData_Paddle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




glm::vec3 Offset_Paddle(float fElapsedTime)
{
     return glm::vec3(-5.0f+(float)mouse_x_Paddle, -4.0f+(float)mouse_y_Paddle, -15.0f);
}

//Similar to the struct in Ball.cpp
//This struct defines methods to create an instance of the paddle and calculate the next position of the paddle at a given time
//It computes the position by computing a translation matrix to "translate" the paddle to its position
struct Instance_Paddle
{
    typedef glm::vec3(*OffsetFunc)(float);

    OffsetFunc CalcOffset;

    glm::mat4 ConstructMatrix(float fElapsedTime)
    {
        glm::mat4 theMat(1.0f);

        theMat[3] = glm::vec4(CalcOffset(fElapsedTime), 1.0f);

        return theMat;
    }
};


//Instance list of the paddle
Instance_Paddle g_instanceList[] =
{
    {Offset_Paddle},
};



//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void Paddle::initPaddle()
{
    InitializeProgramPaddle();
    InitializeVertexBuffer();

    glGenVertexArrays(1, &vao_Paddle);
    glBindVertexArray(vao_Paddle);

    size_t colorDataOffset = sizeof(float) * 4 * numberOfVertices_Paddle;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Paddle);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_Paddle);

    glBindVertexArray(0);

}



//Called to update the display.
void Paddle::displayPaddle()
{
   
    glUseProgram(theProgram_Paddle);

    glBindVertexArray(vao_Paddle);

    float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 500.0f;

    Instance_Paddle &currInst = g_instanceList[0];
    const glm::mat4 &transformMatrix = currInst.ConstructMatrix(fElapsedTime);

    glUniformMatrix4fv(modelToCameraMatrixUnif_Paddle, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData_Paddle), GL_UNSIGNED_SHORT, 0);


    glBindVertexArray(0);
    glUseProgram(0);

    
}




//Called whenever the window is resized. The new window size is given, in pixels.
void Paddle::reshapePaddle (int w, int h)
{
    const float fFrustumScale_Paddle = CalcFrustumScalePaddle(45.0f);

    cameraToClipMatrix_Paddle[0].x = fFrustumScale_Paddle * (h / (float)w);
    cameraToClipMatrix_Paddle[1].y = fFrustumScale_Paddle;

    glUseProgram(theProgram_Paddle);
    glUniformMatrix4fv(cameraToClipMatrixUnif_Paddle, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix_Paddle));
    glUseProgram(0);

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}




//Called whenever a key on the keyboard was pressed.
void Paddle::keyboardPaddle(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        glutLeaveMainLoop();
        return;
    }

//The a,d,w,s keys control the paddle
    if (key=='a')
    {
        mouse_x_Paddle-=1;
    }
    if (key=='d')
    {
        mouse_x_Paddle+=1;
    }
    if (key=='w')
    {
        mouse_y_Paddle+=1;
    }
    if (key=='s')
    {
        mouse_y_Paddle-=1;
    }

}


void Paddle::mouse_funcPaddle(int x,int y)
{
    ;
}
