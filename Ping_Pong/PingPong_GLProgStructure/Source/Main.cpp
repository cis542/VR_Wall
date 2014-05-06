/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Main.cpp
*
*
*/


#include "../Headers/GlutWindow.h"
#include "../Headers/Pad.h"
#include "../Headers/Sphere.h"
#include "../Headers/Corridor.h"
#include "../Headers/Draw.h"
#include "../Headers/Collision.h"



#include "../Headers/VRPNClient.h"
#include "../Headers/inputWii.h"

GlutWindow win(640,640,"Ping Pong",45,1.0,-1.0);
VRPNClient VClient;
InputWii Wii("00:17:AB:39:4E:C5");
Vector initPos = Vector(0.5,0.13,0);
Vector initVel = Vector(0,0,-0.3);

Sphere ball (0.1, initVel, initPos);
Corridor cor;
Pad pad;



// Called after every 100ms to update the position and the velocity of the ball
// Updates the display before returning
void updateState(int value){


	VClient.readData();
	float x_pos = VClient.getXData();
	float y_pos = (VClient.getYData()*sin(0.263) - VClient.getZData()*cos(0.263));
	pad.updatePadPosition(x_pos, y_pos, pad.getZPos());
	Vector ballVel = isCollidingWithWall(ball,cor);
	ball.setVelocity(ballVel);
	ballVel = isCollidingWithPad(ball,pad);
	ball.setVelocity(ballVel);
	ball.updatePosition(100);  
	glutTimerFunc(100,updateState,0);
	glutPostRedisplay();

}

// Draw the entities according to their latest position
void Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);
        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-3.0f);
	drawCorridor();
	drawSphere(ball);
	drawPad(pad);
	glutSwapBuffers();
}

/*
// NOTE: DEBUGGED WITH KEYBOARD AS INPUT DEVICE. COMMENT OUT
// WHEN USING THE VIRTUAL WALL SET UP
void keyboard(int key, int x, int y){
	Vector padPos = pad.getPadPosition();
	switch(key){
		case GLUT_KEY_UP:
			
			if(padPos[1] < 1.0){
				padPos[1] += 0.01;
			}
			break;	

		case GLUT_KEY_DOWN:
			if (padPos[1] > -1.0){
				padPos[1] -= 0.01;
			}
			break;

		case GLUT_KEY_LEFT:
			if (padPos[0] < 1.0){
				padPos[0] += 0.01;
			}
			break;

		case GLUT_KEY_RIGHT:
			if (padPos[0] > -1.0){
				padPos[0] -= 0.01;
			}
			break;
		
		default:
			break;
	}
	pad.updatePadPosition(padPos);
}
*/

// Initialize the GL parameters
void init(){

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(win.getWidth(),win.getHeight());
	glutInitWindowPosition(100, 100);
	glutCreateWindow((win.getTitle()).c_str());
	glutDisplayFunc(Draw);
	glutSpecialFunc(keyboard);	                         //NOTE: COMMENT THIS LINE WHEN USING THE VIRTUAL WALL SETUP
	glutTimerFunc(100, updateState, 0);
	glClearColor(0.8, 0.8, 0.8, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_PROJECTION);				
	
	glViewport(0, 0, win.getWidth(), win.getHeight());		
	glMatrixMode(GL_PROJECTION);				
	glLoadIdentity();					
	GLfloat aspect = (GLfloat) win.getWidth() / win.getHeight();
	gluPerspective(win.getFOVA(), aspect, win.getZNear(), win.getZFar());
	glMatrixMode(GL_MODELVIEW);						
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f ); 							
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );			
		
}
int main(int argc, char **argv)
{
	VClient.connectToServer("Wand@158.130.62.115:3883");
	
	glutInit(&argc,argv);	
	init();
	
	glutMainLoop();
	return 0;
}
