/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Pad.h
*
*/

#pragma once

#include "Sphere.h"


class Pad{

	static float ZPosition;
	Vector position;
	float radius;

	public:
	Pad();
	void updatePadPosition(Vector pos);
	void setRadius(float w);

	float getRadius() const;	
	Vector getPadPosition() const;

	static float getZPos(){ return ZPosition;}
};

