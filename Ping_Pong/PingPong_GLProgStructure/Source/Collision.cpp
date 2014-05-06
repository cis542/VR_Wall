/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Collision.cpp
*
*/
#include "../Headers/Collision.h"

// Detects the collision of the ball with the walls. Collision is elastic
// If collision detected, the function returns the reflected velocity vector
// else it returns the original velocity
Vector isCollidingWithWall(const Sphere&s, const Corridor& cor){

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

Vector isCollidingWithPad(const Sphere&s, const Pad& p){

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
			if (padPosition[2] - spherePosition[2] < s.getRadius() && retVal[2] > 0){
				temp = Vector(0,0,-1);
				retVal.reflectAbout(temp);
			}
		}
		else if ( total_dist <= barrier ){
			if (padPosition[2] - spherePosition[2] < s.getRadius()){
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



