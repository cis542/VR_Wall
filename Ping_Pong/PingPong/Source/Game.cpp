/*
* 
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Game.cpp
*
*/

#include "../Headers/Game.h"


// Initialize the Window, the ball and openGL parameters
Game::Game() : win(640,480,"Ping pong",45,1.0,-1.0),ball (0.1, Vector(0,0,-0.3), Vector(0.5,0.13,0)) {
   initializeGL();
}

Game::~Game(){
	
}


float Game::alpha = 0.263;

// Connect to the input devices
void Game::connectToInputs( const std::string& wandAddr){
   
   VClient.connectToServer(wandAddr);
   
}



// Initializes the OpenGL parameters

void Game::initializeGL(){


   glutInitWindowSize(win.getWidth(),win.getHeight());
   glutInitWindowPosition(100, 100);
   glutCreateWindow((win.getTitle()).c_str());
   glutDisplayFunc(Draw);	
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


//Draws the corridor as well as the pad and the ball according to their latest updated position
void Game::Draw()
{

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

// This timer function is called repeatedly
// with the time interval between two calls as 100ms
// It reads the data from the input devices
// and updates the position of the pad.
// Detection of the collision of the ball with the wall as well as

void Game::updateState(int value){
 
   VClient.readData();

   //TODO : find the scale factor with which x_pos & y_pos need to be multiplied to limit them between -1.0 and 1.0
   float x_pos = VClient.getXData(); 
   float y_pos = (VClient.getYData()*sin(alpha) - VClient.getZData()*cos(alpha));

   Vector ballVel = isCollidingWithWall(ball,cor);
   ball.setVelocity(ballVel);
   ballVel = isCollidingWithPad(ball,pad);
   ball.setVelocity(ballVel);
   ball.updatePosition(100);
   pad.updatePadPosition(Vector(x_pos,y_pos,Pad::getZPos()));

   glutTimerFunc(100,updateState,0);
   glutPostRedisplay();
}

// Launch the OpenGL main loop
void Game::startGame(){
   glutMainLoop();
}



// Detects the collision of the ball with the walls. Collision is elastic
// If collision detected, the function returns the reflected velocity vector
// else it returns the original velocity
Vector Game::isCollidingWithWall(const Sphere&s, const Corridor& cor){

	Vector retVal = s.getVelocity();
	Vector spherePosition = s.getPosition();
	Vector temp;

	if (pow((spherePosition[0] - cor.getLW()),2) < pow((s.getRadius()),2)){
		temp = Vector(-1,0,0);
		retVal.reflectAbout(temp);
	}
	else if ( pow((cor.getRW() - spherePosition[0]),2) < pow((s.getRadius()),2)){
		temp = Vector(1,0,0);
		retVal.reflectAbout(temp);
	} 
	else if ( pow((cor.getTW() - spherePosition[1]),2) < pow((s.getRadius()),2)){
		temp = Vector(0,-1,0);
		retVal.reflectAbout(temp);
	}
	else if (pow((spherePosition[1] - cor.getBW()),2) < pow((s.getRadius()),2)){
		temp = Vector(0,1,0);
		retVal.reflectAbout(temp);
	}
	else if (pow((spherePosition[2] - cor.getFW()),2) < pow((s.getRadius()),2)){
		temp = Vector(0,0,1);
		retVal.reflectAbout(temp);
	}
	
	return retVal;
}	



// Detects the collision of the ball with the pad. Collision if present is elastic.
// Affects the velocity of the ball only if the vertical plane passing through 
// the center of the ball lies farther than the vertical plane
// passing through the pad
// If collision detected, the function returns the reflected velocity vector
// else it returns the original velocity

Vector Game::isCollidingWithPad(const Sphere&s, const Pad& p){

	Vector retVal = s.getVelocity();
	Vector spherePosition = s.getPosition();
	Vector padPosition = p.getPadPosition();
	Vector temp;

	float total_dist = pow(padPosition[0]-spherePosition[0],2)+pow(padPosition[1]-spherePosition[1],2) + pow(padPosition[2]-spherePosition[2],2);
	total_dist = pow(total_dist, 0.5);

	float xydist = pow(padPosition[0]-spherePosition[0],2)+pow(padPosition[1]-spherePosition[1],2);
	xydist = pow(xydist,0.5);

	float barrier = pow(s.getRadius(),2) + pow(p.getRadius(),2) + 2*s.getRadius()*p.getRadius()*(xydist-p.getRadius())/s.getRadius();
	barrier = pow(barrier,0.5);
	if (spherePosition[2] < padPosition[2]){
		if (xydist <= p.getRadius()){
			// Perpendicular collision
			if (padPosition[2] - spherePosition[2] < s.getRadius() && retVal[2] > 0){
				temp = Vector(0,0,-1);
				retVal.reflectAbout(temp);
			}
		}
		else if ( total_dist <= barrier ){
			if (padPosition[2] - spherePosition[2] < s.getRadius()){
				// Obtuse collision
				float x_diff = spherePosition[0] - padPosition[0];
				float y_diff = spherePosition[1] - padPosition[1];
				float z_diff = spherePosition[2] - padPosition[2];
				float s1 = pow(x_diff,2) + pow(y_diff,2);
				s1 = pow(s1,0.5);
				
				x_diff = spherePosition[0] - (padPosition[0] + p.getRadius()*x_diff/s1);
				y_diff = spherePosition[1] - (padPosition[1] + p.getRadius()*y_diff/s1);
				
				float s = pow(x_diff,2) + pow(y_diff,2) + pow(z_diff,2);
				s = pow(s,0.5);
				temp[0] = x_diff/s;
				temp[1] = y_diff/s;
				temp[2] = z_diff/s;
				
				retVal.reflectAbout(temp);
			}
		}
	}
	return retVal;
}



// Draws the Circular translucent Pad
// The x component is negated to account for the opposite x axis convention used by openGL.
void Game::drawPad(Pad& p)const{
	
   float rad = p.getRadius();
   Vector pos = p.getPadPosition();	
   
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);
   glBegin(GL_TRIANGLE_FAN);
   glColor4f(1.0f, 0.4f, 0.4f, 0.5f);
   for (int i=0; i < 360; i++)
   {
   	float degInRad = i*M_PI/180;
   	glVertex3f(-pos[0]+rad*cos(degInRad),pos[1]+rad*sin(degInRad),pos[2]);
   }
   glEnd();
}

// Draws the sphere onto the screen.
// The x component is negated to account for the opposite x axis convention used by openGL. 
void Game::drawSphere(const Sphere& s) const{
	int i,j;
	int lats = 100;
	int longs = 100;
	Vector center = s.getPosition();
	float rad = s.getRadius();
	
	for (i=0;i<= lats;i++){
		float lat0 = M_PI*(-0.5 + (float)(i-1)/lats);
		float z0 = sin(lat0);
		float zr0 = cos(lat0);
		
		float lat1 = M_PI*(-0.5 + (float)i/lats);
		float z1 = sin(lat1);
		float zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++){
			float lng = 2*M_PI*(float)(j-1)/longs;
			float x = cos(lng);
			float y = sin(lng);

			glNormal3f(-center[0] + rad*x*zr0, center[1] + rad*y*zr0,center[2] +  rad*z0);
			glVertex3f(-center[0] + rad*x*zr0, center[1] + rad*y*zr0,center[2] +  rad*z0);
			glNormal3f(-center[0] + rad*x*zr1, center[1] + rad*y*zr1,center[2] +  rad*z1);
			glVertex3f(-center[0] + rad*x*zr1, center[1] + rad*y*zr1,center[2] +  rad*z1);
		}
		glEnd();
	}
}


//Draws the Corridor
void Game::drawCorridor() const{
   
   int width, height;
   int * data;
   FILE * file;

   GLuint texture;
   
   glGenTextures( 1, &texture );
   glBindTexture( GL_TEXTURE_2D, texture );
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		
   width = 543;
   height = 612;

   data = (int*)malloc( width * height * 3 );

   file = fopen( "24bit.bmp", "rb" );
   fread( data, width * height * 3, 1, file );
   fclose( file );
   gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );

   free( data );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, texture );

   
   glBegin(GL_QUADS);
   glTexCoord2d(0,0);glVertex3f(-1,-1,-1);
   glTexCoord2d(0,1);glVertex3f(1,-1,-1);
   glTexCoord2d(1,1);glVertex3f(1,1,-1);
   glTexCoord2d(1,0);glVertex3f(-1,1,-1);

   glTexCoord2d(0,0);glVertex3f(-1,-1,1);
   glTexCoord2d(0,1);glVertex3f(-1,-1,-1);
   glTexCoord2d(1,1);glVertex3f(-1,1,-1);
   glTexCoord2d(1,0);glVertex3f(-1,1,1);

   glTexCoord2d(0,0);glVertex3f(-1,-1,1);
   glTexCoord2d(0,1);glVertex3f(1,-1,1);
   glTexCoord2d(1,1);glVertex3f(1,-1,-1);
   glTexCoord2d(1,0);glVertex3f(-1,-1,-1);

   glTexCoord2d(0,0);glVertex3f(1,-1,1);
   glTexCoord2d(0,1);glVertex3f(1,1,1);
   glTexCoord2d(1,1);glVertex3f(1,1,-1);
   glTexCoord2d(1,0);glVertex3f(1,-1,-1);

   glTexCoord2d(0,0);glVertex3f(-1,1,1);
   glTexCoord2d(0,1);glVertex3f(1,1,1);
   glTexCoord2d(1,1);glVertex3f(1,1,-1);
   glTexCoord2d(1,0);glVertex3f(-1,1,-1);

   
   glEnd();
   glDisable( GL_TEXTURE_2D );
}
