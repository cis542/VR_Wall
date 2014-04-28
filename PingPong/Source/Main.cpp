/*
*
* Ping Pong
* Author: Aditya
* Main.cpp
*
*
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "../Headers/Tools.h"



void drawSphere(const Sphere& s);
Vector isCollidingWithPad(const Sphere&s, const Pad& p);
Vector isColliding(const Sphere&s, const Corridor& cor);

typedef struct {
    int width;
	int height;
	char* title;
	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;

Vector initPos = Vector(0,0.13,0);
Vector initVel = Vector(0,0,-0.3);

Sphere ball (0.1, initVel, initPos);
Corridor cor;
Pad pad;

void init(){
	GLfloat sun_direction[] = {0.0, 2.0, -1.0, 1.0};
	GLfloat sun_intensity[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat ambient_intensity[] = {0.3, 0.3, 0.3, 1.0};

	glClearColor(0.8, 0.8, 0.8, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(0.5,0.5,0.5,0.5,-1.1,1.1);
	//gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_PROJECTION);				// select projection matrix
	
	glViewport(0, 0, win.width, win.height);						// set the viewport
	glMatrixMode(GL_PROJECTION);								// set matrix mode
	glLoadIdentity();								// reset projection matrix
	GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
	glMatrixMode(GL_MODELVIEW);							// specify which matrix is the current matrix
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f ); 							// specify the clear value for the depth buffer
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
		
}

// Called after every 100ms to update the display
void timerReDisplay(int value){
  
	glutTimerFunc(100,timerReDisplay,0);
	glutPostRedisplay();

}

void reDraw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);

        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-3.0f);
	Vector ballVel = isColliding(ball,cor);
	ball.setVelocity(ballVel);
	ballVel = isCollidingWithPad(ball,pad);
	ball.setVelocity(ballVel);
	ball.updatePosition(100);
	drawSphere(ball);
	drawPad(pad);
	glutSwapBuffers();
}



int main(int argc, char **argv)
{
	//   VClient.connectToServer("Wand@158.130.62.115:3883");
	// set window values
	win.width = 640;
	win.height = 480;
	
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = -1.0f;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowSize(win.width,win.height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ping Pong");
	glutDisplayFunc(reDraw);
	
	glutTimerFunc(100, timerReDisplay, 0);
	
	init();
	
	glutMainLoop();
	return 0;
}
