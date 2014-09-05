/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Draw.cpp
*
*/


#include "../Headers/Draw.h"
#include <stdio.h>


// Draws the Circular translucent Pad
// The x component is negated to account for the opposite x axis convention used by openGL.
void drawPad(Pad& p){
	
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
void drawSphere(const Sphere& s){
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
void drawCorridor(){
   
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
