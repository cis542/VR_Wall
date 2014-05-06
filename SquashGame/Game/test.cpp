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
#include "Ball.h"




glm::vec3 initPos = glm::vec3(0.0f,0.0f,-15.0f);
glm::vec3 initVel = glm::vec3(0.0f,0.0f,-0.3f);

Paddle paddle_obj;
Ball ball_obj(initVel, initPos);
//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glEnable(GL_DEPTH_CLAMP);

	ball_obj.index_draw=0;
	paddle_obj.initPaddle();
	ball_obj.initBall();

}

//Called to update the display.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	paddle_obj.displayPaddle();
	ball_obj.displayBall();

	glutSwapBuffers();
    glutPostRedisplay();

}

//Called whenever the window is resized. The new window size is given, in pixels.
void reshape (int w, int h)
{
	
	paddle_obj.reshapePaddle(w,h);
	ball_obj.reshapeBall(w,h);

}

//Called whenever a key on the keyboard was pressed.
void keyboard(unsigned char key, int x, int y)
{
	paddle_obj.keyboardPaddle(key,x,y);
	ball_obj.keyboardBall(key,x,y);

}

void mouse_func(int x,int y)
{
	;
}

//Called before FreeGLUT is initialized. It should return the FreeGLUT
//display mode flags that you want to use
//This function can also set the width/height of the window.
unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
