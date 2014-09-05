/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Sphere.cpp
*
*
*/

#include "../Headers/Sphere.h"

Sphere::Sphere(float r, Vector v, Vector p):radius(r),velocity(v),position(p){

}

Sphere::~Sphere(){

}

// Sets the position of the sphere
void Sphere::setPosition(Vector& pos){
	position = pos;	
}

// Updates the position of the ball according to the equation
// s(n) = s(n-1) + v(n)*dt
void Sphere::updatePosition(float dt){

	position[0] = position[0] + velocity[0]*dt/1000;
	position[1] = position[1] + velocity[1]*dt/1000;
	position[2] = position[2] + velocity[2]*dt/1000;	
}


void Sphere::setVelocity(Vector& vel){
	velocity = vel;
}


Vector Sphere::getPosition () const{
	return position;
}


Vector Sphere::getVelocity() const{
	return velocity;
}


float Sphere::getRadius() const{
	return radius;
}

	

