/*
 * main.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: Jing, Aditya
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
#include "../Header Files/VRPNClient.h"
#include "../Header Files/inputWii.h"
//#include "WinUser.h"

#define NUM_BLOCKS 2
#define PI 3.1459
VRPNClient VClient;
//InputWii Wii("00:17:AB:39:4E:C5");

Block Blocks[NUM_BLOCKS];
//Block::BlockList list;//[NUM_BLOCKS];

double x_pos, y_pos, z_pos;

Scene theScene;

vec3 GetOGLPos(int x, int y, int z);  //take in coordinates from the optitrack and return the OpenGL coordinates

void initBlocks();

//vec3 initialPos1 = vec3(0.3,0.2,0);
//vec3 initialPos2 = vec3(0.5,1.0,0);

vec3 initialPos[NUM_BLOCKS];


double alpha;
double x_point;
double y_point;
double z_point;

//void rotateView(double dest, double inc);

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;


glutWindow win;

vec3 openGLPosition = vec3();   //global World coordinates



//UI helpers
int theButtonState = 0;

bool isRunning = true;

void onTimerCb(int value)
{
 
 
 VClient.readData();
 x_pos = 2*VClient.getXData();
 y_pos = 2*(VClient.getYData()*sin(0.263) - VClient.getZData()*cos(0.263));
	
 z_pos = 2*(VClient.getZData()*sin(0.263) + VClient.getYData()*cos(0.263));
 
 //printf("%f %f %f\n", x_pos,y_pos,z_pos);

 theButtonState = 0;//Wii.GetButtonId();
  

 if (theButtonState == 8){
 	for (int i=0; i< 2;i++){
		if (Blocks[i].IsInside(x_point, y_point, z_point)){
			Blocks[i].held_flag = 1;

		}
		else{
			Blocks[i].held_flag = 0;
		}
 	}
 }
 else{
 	for (int i=0; i< 2;i++){
		
		Blocks[i].held_flag = 0;
		
 	}
 }
 if (theButtonState == 512)
 {
	alpha = alpha + 10;
 }
 if (theButtonState == 256)
 {
	alpha = alpha - 10;
 }

 x_point = x_pos*cos(alpha*PI/180) + z_pos*sin(alpha*PI/180);
 y_point = y_pos;
 z_point = z_pos*cos(alpha*PI/180) - x_pos*sin(alpha*PI/180);
 glutTimerFunc(100,onTimerCb,0);

 for (int i = 0; i < NUM_BLOCKS; i++){		
 	if(isRunning)
 	{
	 Blocks[i].Update(0.01, theScene);
 	}
}

 glutPostRedisplay();

}

void onDrawCb()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-3.0f);
    glRotatef(alpha,0,1,0);
    /*
	glColor3f(1.0,1.0,1.0);
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	*/

        theScene.Draw(win.z_near-win.z_far,2);

        for(int i=0;i<NUM_BLOCKS;i++)
        {
	Blocks[i].Draw(Blocks[i].updateCenter(Blocks[i].m_vparticles));    //give initial coordinates
	}

        glColor3f(1.0f,0.0f,0.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex3f(x_point,y_point,z_point);
	
	glEnd();
	//glutSwapBuffers();

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

/*
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
*/

	    glMatrixMode(GL_PROJECTION);												// select projection matrix
	    glViewport(0, 0, win.width, win.height);									// set the viewport
	    glMatrixMode(GL_PROJECTION);												// set matrix mode
	    glLoadIdentity();															// reset projection matrix
	    GLfloat aspect = (GLfloat) win.width / win.height;

	    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
	    glMatrixMode(GL_MODELVIEW);												// specify which matrix is the current matrix
	    glShadeModel( GL_SMOOTH );
	    glClearDepth( 1.0f );														// specify the clear value for the depth buffer
	    glEnable( GL_DEPTH_TEST );
	    glDepthFunc( GL_LEQUAL );
	    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
            glClearColor(0.0, 0.0, 0.0, 1.0);											// specify clear values for the color buffers


}

void initBlocks()
{
	initialPos[0] = vec3(0.0, 0.0 , 0.0);
	initialPos[1] = vec3(0.4, 1.0 , 0.0);
	//initialPos[2] = vec3(-0.4, 1.0 , 0.0);
	//initialPos[3] = vec3(0, 0.25 , 0);
	//initialPos[4] = vec3(0.5, 0 , 0);
	//initialPos[5] = vec3(0.5, 1 , 0);
  	for (int i = 0; i < NUM_BLOCKS; i++){
      		Blocks[i].InitBlock(initialPos[i], 0.5, 0.5, 0.5);
      		Blocks[i].SetBlockIndex(i);
     	 	Block::AddToList(&Blocks[i]);
      	}
}

int main(int argc, char **argv)
{
	   VClient.connectToServer("Wand@158.130.62.115:3883");
	// set window values
	   win.width = 640;
	   win.height = 480;
	//win.title = "OpenGL/GLUT Example. Visit http://openglsamples.sf.net ";
	   win.field_of_view_angle = 45;
	   win.z_near = 1.0f;
	   win.z_far = -1.0f;
	    //printf("hello world");
	    initBlocks();

	    glutInit(&argc, argv);
	    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	    //glutInitWindowSize(640, 480);

	    glutInitWindowSize(win.width,win.height);
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
/*
void rotateView(double dest, double inc)
{
	
	double orig = inc;
	double x_temp, y_temp;
	vec3 temp[NUM_BLOCKS];
	printf("%f\n",orig);
	for (int i=0; i <NUM_BLOCKS; i++)
	{
		temp[i] = Blocks[i].updateCenter(Blocks[i].m_vparticles);
	}
	//while (orig != dest)
	//{
		for (int i=0; i < NUM_BLOCKS; i++)
		{
			x_temp = temp[i][0]*cos(orig*PI/180) + temp[i][1]*sin(orig*PI/180);
			y_temp = -temp[i][0]*sin(orig*PI/180) + temp[i][1]*cos(orig*PI/180);
			temp[i][0] = x_temp;
			temp[i][1] = y_temp;
			Blocks[i].Draw(temp[i]);
		}
		
		orig = orig+inc;
	//}
}
*/	
		

