/*
*
* Ping Pong
* Author: Aditya
* Tools.h
*
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Vector.h"
#include "Corridor.h"

class Sphere{

	double radius;
	Vector velocity;
	Vector position;
	
	public:

	Sphere(double r, Vector v, Vector p);
	~Sphere();
	void setPosition(Vector& pos);
	void setVelocity(Vector& vel);
	void updatePosition(double dt);
	Vector getPosition () const;
	Vector getVelocity () const;
	double getRadius () const;

};

 
	
class Pad{
	Vector position;
	double radius;

	public:
	Pad();
	void updatePadPosition(Vector& pos);
	double getRadius() const;
	void setRadius(double w);
	
	Vector getPadPosition() const;
	
	friend void drawPad(Pad& p){
	
		double rad = p.radius;
	
		double x = p.position[0];
		double y = p.position[1];
		double z = p.position[2];

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1.0f, 0.4f, 0.4f, 0.5f);
	
		for (int i=0; i < 360; i++)
   		{
      			float degInRad = i*3.14/180;
      			glVertex3f(x+rad*cos(degInRad),y+rad*sin(degInRad),z);
   		}
		glEnd();
	}



};
	
