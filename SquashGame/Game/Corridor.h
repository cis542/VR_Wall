#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

//This class defines the corridor that the ball bounces off of
class Corridor{
	

    //These values represent the limits in terms of co-ordinates of the walls
    //As of now the ball bounces off of imaginary walls. The walls have not been drawn
    float rightWall;
    float leftWall;
    float topWall;
    float bottomWall;
    float farWall;
	
	public:

    //These methods return the co-ordinates of the walls
    //These are used in Ball.cpp to compare the co-ordinates if the wall with the co-ordinates of the ball
    float getRW() const;
    float getLW() const;
    float getTW() const;
    float getBW() const;
    float getFW() const;
	Corridor();
};
