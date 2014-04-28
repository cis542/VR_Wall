/*
*
* PingPong
* Author: Aditya
* Corridor.h
*
*
*/
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

class Corridor{
	
	double rightWall;
	double leftWall;
	double topWall;
	double bottomWall;
	double farWall;
	
	public:

	double getRW() const;
	double getLW() const;
	double getTW() const;
	double getBW() const;
	double getFW() const;
	Corridor();
};
