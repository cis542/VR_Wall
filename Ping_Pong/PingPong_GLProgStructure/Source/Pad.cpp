/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Pad.cpp
*
*/

#include "../Headers/Pad.h"

float Pad::ZPosition = 0.5;

Pad::Pad(): position(Vector(0,0,ZPosition)),radius(0.1){

}

void Pad::updatePadPosition(Vector pos){
	position = pos;
}

float Pad::getRadius() const{
	return radius;
}


void Pad::setRadius(float r){
	radius = r;
}

Vector Pad::getPadPosition() const{
	return position;
}


