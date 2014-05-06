/*
*
* Project: VR Wall
* Game: PingPong
* Author: Aditya
* Corridor.cpp
*
*/

#include "../Headers/Corridor.h"

Corridor::Corridor():leftWall(1.0),rightWall(-1.0),topWall(1.0),bottomWall(-1.0),farWall(-1.0){

}

float Corridor::getRW() const{
	return rightWall;
}

float Corridor::getLW() const{
	return leftWall;
}

float Corridor::getTW() const{
	return topWall;
}

float Corridor::getBW() const{
	return bottomWall;
}

float Corridor::getFW() const{
	return farWall;
}


