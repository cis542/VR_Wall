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
#include "Ball.h"
#include "Corridor.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


GLuint theProgram_Ball;

Corridor cor;


GLuint modelToCameraMatrixUnif_Ball;
GLuint cameraToClipMatrixUnif_Ball;

glm::mat4 cameraToClipMatrix_Ball;

const int numberOfVertices_Ball = 8;

#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData_Ball[] =
{
    +1.0f, +1.0f, +1.0f,
    -1.0f, -1.0f, +1.0f,
    -1.0f, +1.0f, -1.0f,
    +1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    +1.0f, +1.0f, -1.0f,
    +1.0f, -1.0f, +1.0f,
    -1.0f, +1.0f, +1.0f,

    GREEN_COLOR,
    BLUE_COLOR,
    RED_COLOR,
    BROWN_COLOR,

    GREEN_COLOR,
    BLUE_COLOR,
    RED_COLOR,
    BROWN_COLOR,
};

const GLshort indexData_Ball[] =
{
    0, 1, 2,
    1, 0, 3,
    2, 3, 0,
    3, 2, 1,

    5, 4, 6,
    4, 5, 7,
    7, 6, 4,
    6, 7, 5,
};

GLuint vertexBufferObject_Ball;
GLuint indexBufferObject_Ball;
GLuint vao_Ball;


Ball::Ball(glm::vec3 v, glm::vec3 p):velocity(v),position(p){

}
Ball::~Ball()
{

}


glm::vec3 Ball::updatePosition(float dt){

    position[0] = position[0] + velocity[0]*dt/1000;
    position[1] = position[1] + velocity[1]*dt/1000;
    position[2] = position[2] + velocity[2]*dt/1000;

    return position;
}

void Ball::setVelocity(glm::vec3& vel){
    velocity = vel;
}

glm::vec3 Ball::getPosition () const{
    return position;
}

glm::vec3 Ball::getVelocity() const{
    return velocity;
}



float Ball::CalcFrustumScaleBall(float fFovDeg)
{
    const float degToRad = 3.14159f * 2.0f / 360.0f;
    float fFovRad = fFovDeg * degToRad;
    return 1.0f / tan(fFovRad / 2.0f);
}



void Ball::InitializeProgramBall()
{
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "PosColorLocalTransform.vert"));
    shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "ColorPassthrough.frag"));

    theProgram_Ball = Framework::CreateProgram(shaderList);

    modelToCameraMatrixUnif_Ball = glGetUniformLocation(theProgram_Ball, "modelToCameraMatrix");
    cameraToClipMatrixUnif_Ball = glGetUniformLocation(theProgram_Ball, "cameraToClipMatrix");

    float fzNear = 1.0f; float fzFar = 1000.0f;

    const float fFrustumScale_Ball = CalcFrustumScaleBall(45.0f);

    cameraToClipMatrix_Ball[0].x = fFrustumScale_Ball;
    cameraToClipMatrix_Ball[1].y = fFrustumScale_Ball;
    cameraToClipMatrix_Ball[2].z = (fzFar + fzNear) / (fzNear - fzFar);
    cameraToClipMatrix_Ball[2].w = -1.0f;
    cameraToClipMatrix_Ball[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

    glUseProgram(theProgram_Ball);
    glUniformMatrix4fv(cameraToClipMatrixUnif_Ball, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix_Ball));
    glUseProgram(0);
}




void Ball::InitializeVertexBuffer()
{
    glGenBuffers(1, &vertexBufferObject_Ball);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Ball);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData_Ball), vertexData_Ball, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &indexBufferObject_Ball);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_Ball);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData_Ball), indexData_Ball, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

glm::vec3 Offset_Ball(float fElapsedTime)
{
    glm::vec3 ballVel = isColliding(cor);
    setVelocity(ballVel);
    ballPos=updatePosition(fElapsedTime);
    return ballPos;

}

//The next 2 functions in the code is for defining different motion profiles for different balls
//Code can then be added to have the regular ball interact with these other balls
//The function OvalOffset_Ball creates a ball that moves in an oval pattern, in the x-y plane, which can collide with the main moving ball
//The function BottomCircleOffset_Ball creates a ball that moves in an circular pattern, in the x-z plane, which can collide with the main moving ball
/*glm::vec3 OvalOffset_Ball(float fElapsedTime)
{
    const float fLoopDuration = 3.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;

    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

    return glm::vec3(cosf(fCurrTimeThroughLoop * fScale) * 4.f,
                     sinf(fCurrTimeThroughLoop * fScale) * 6.f,
                     -30.0f);
}

glm::vec3 BottomCircleOffset_Ball(float fElapsedTime)
{
    const float fLoopDuration = 12.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;

    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

    return glm::vec3(cosf(fCurrTimeThroughLoop * fScale) * 8.f,
                     -1.5f,
                     sinf(fCurrTimeThroughLoop * fScale)*5.0f- 64.0f);
}
*/


//This struct defines methods to create an instance of the ball and calculate the next position of the ball at a given time
//It computes the position by computing a translation matrix to "translate" the ball to its position
struct Instance_Ball
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


//Instance list of the ball
//Can be exoanded to include other balls with different motion profiles
Instance_Ball g_instanceList[] =
{
    {Offset_Ball},
    /*{OvalOffset_Ball},
          {BottomCircleOffset_Ball},*/
};




//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void Ball::initBall()
{
    InitializeProgramBall();
    InitializeVertexBuffer();

    glGenVertexArrays(1, &vao_Ball);
    glBindVertexArray(vao_Ball);

    size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices_Ball;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_Ball);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_Ball);

    glBindVertexArray(0);

}



//Called to update the display.
void Ball::displayBall()
{

    glUseProgram(theProgram_Ball);

    glBindVertexArray(vao_Ball);

    float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 500.0f;

    Instance_Ball &currInst = g_instanceList[0];
    const glm::mat4 &transformMatrix = currInst.ConstructMatrix(fElapsedTime);

    glUniformMatrix4fv(modelToCameraMatrixUnif_Ball, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData_Ball), GL_UNSIGNED_SHORT, 0);


    glBindVertexArray(0);
    glUseProgram(0);

}




//Called whenever the window is resized. The new window size is given, in pixels.
void Ball::reshapeBall (int w, int h)
{
    const float fFrustumScale_Ball = CalcFrustumScaleBall(45.0f);

    cameraToClipMatrix_Ball[0].x = fFrustumScale_Ball * (h / (float)w);
    cameraToClipMatrix_Ball[1].y = fFrustumScale_Ball;

    glUseProgram(theProgram_Ball);
    glUniformMatrix4fv(cameraToClipMatrixUnif_Ball, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix_Ball));
    glUseProgram(0);

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}




//Called whenever a key on the keyboard was pressed.
void Ball::keyboardBall(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        glutLeaveMainLoop();
        return;
    }

}


void Ball::mouse_funcBall(int x,int y)
{
    ;
}

//Return velocity vector if collision occurs
glm::vec3 isColliding(const Corridor& cor){

    glm::vec3 retVal = getVelocity();
    glm::vec3 ballPosition = getPosition();
    glm::vec3 temp;

    if (ballPosition[0] < cor.getLW()){
        temp = Vector(1,0,0);
        retVal=reflectAbout(retVal,temp);
    }
    else if ((cor.getRW() < spherePosition[0])){
        temp = Vector(-1,0,0);
        retVal=reflectAbout(retVal,temp);
    }
    else if ((cor.getTW() < spherePosition[1])){
        temp = Vector(0,-1,0);
        retVal=reflectAbout(retVal,temp);
    }
    else if ((spherePosition[1] < cor.getBW())){
        temp = Vector(0,1,0);
        retVal=reflectAbout(retVal,temp);
    }
    else if ((spherePosition[2] > cor.getFW())){
        temp = Vector(0,0,1);
        retVal=reflectAbout(retVal,temp);
    }
    else if ((spherePosition[2] > -15.0f)){
        temp = Vector(0,0,1);
        retVal=reflectAbout(retVal,temp);
    }

    return retVal;
}

void reflectAbout (const glm::vec3& aVec,const glm::vec3& bVec){
    float alpha;
    alpha = -2 * scalarProduct(aVec, bVec);
    aVec[0] = alpha * bVec[0] + aVec[0];
    aVec[1] = alpha * bVec[1] + aVec[1];
    aVec[2] = alpha * bVec[2] + aVec[2];
}

double scalarProduct( const Vector& aVec, const Vector& bVec){

    double retVal;
    retVal = aVec[0]*bVec[0] + aVec[1]*bVec[1] + aVec[2]*bVec[2];

    return retVal;
}
