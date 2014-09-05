/*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Tools.h
*
*/
#pragma once

#include "Vector.h"


class Sphere{

	float radius;
	Vector velocity;
	Vector position;
	
	public:

	Sphere(float r, Vector v, Vector p);
	~Sphere();
	void setPosition(Vector& pos);
	void setVelocity(Vector& vel);
	void updatePosition(float dt);
	Vector getPosition () const;
	Vector getVelocity () const;
	float getRadius () const;

	
};

