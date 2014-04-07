/*
 * main.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: vrwall
 */

#include <stdio.h>
#include <math.h>
#include <fstream>
#include <GL/glut.h>
//#include "GL/GL.h"
//#include <IL/il.h>
//#include <IL/ilu.h>
//#include <IL/ilut.h>
#include <iostream>
#include <stdarg.h>

#include <stdlib.h>

#include "../Header Files/Block.h"
#include "../Header Files/Scene.h"
//#include "WinUser.h"

Block theBlock;

Scene theScene;

vec3 GetOGLPos(int x, int y, int z);  //take in coordinates from the optitrack and return the OpenGL coordinates

void initBlocks();

vec3 openGLPosition = vec3();   //global World coordinates

vec3 initialPos = vec3(0,0,0);

//UI helpers
int theButtonState = 0;

bool isRunning = true;

void onTimerCb(int value)
{
 glutTimerFunc(100,onTimerCb,0);
 if(isRunning)
 {
	 theBlock.Update(0.01, theScene);

 }


}

void onDrawCb()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0,1.0,1.0);
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);


	theBlock.Draw(theBlock.m_center);    //give initial coordinates
	glutSwapBuffers();

}

vec3 GetOGLPos(int x, int y, int z)
{
	//TODO
	vec3 res = vec3();
	return res;
}

void init(void)
{
glClearColor(0.8,0.8,0.8,1.0);

glEnable(GL_BLEND);
glEnable(GL_ALPHA_TEST);
//glBlendFunc(Gl_SRC_AlPHA,GL_ONE_MINUS_SRC_ALPHA);   //??what's the function do?

glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
glShadeModel(GL_SMOOTH);

glEnable(GL_NORMALIZE);

glCullFace(GL_FRONT);

float white[4] = {1.0,1.0,1.0,1.0};
float black[4] = {0.0,0.0,0.0,1.0};
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
glLightfv(GL_LIGHT0, GL_SPECULAR, white);
glLightfv(GL_LIGHT0, GL_AMBIENT, black);

GLfloat fogColor[4]= {0.8f, 0.8f, 0.8f, 1.0f};
glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
glFogf(GL_FOG_DENSITY, 0.35f);				// How Dense Will The Fog Be
glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
glFogf(GL_FOG_START, 10.0f);				// Fog Start Depth
glFogf(GL_FOG_END, 40.0f);				// Fog End Depth
glEnable(GL_FOG);



}

void initBlocks()
{
  theBlock.InitBlock(initialPos, 0.5, 0.5, 0.5);
}

int main(int argc, char **argv)
{
	    
	    initBlocks();

	    glutInit(&argc, argv);
	    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	    glutInitWindowSize(640, 480);
	    glutInitWindowPosition(100, 100);
	    glutCreateWindow("BlockSim!!");
	    glutDisplayFunc(onDrawCb);
	    //glutKeyboardFunc(onKeyboardCb);
	    //glutSpecialFunc(onKeyboardSpecialCb);
	    //glutMouseFunc(onMouseCb);
	    //glutMotionFunc(onMouseMotionCb);
	    glutTimerFunc(100, onTimerCb, 0);
	    //glutReshapeFunc(onResizeCb);
	    
	    init();
		
	    glutMainLoop();
	    return 0;

}


