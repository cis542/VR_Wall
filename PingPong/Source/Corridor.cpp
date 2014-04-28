/*
*
* PingPong
* Author: Aditya
* Corridor.cpp
*
*/

#include "../Headers/Corridor.h"

Corridor::Corridor():leftWall(1.0),rightWall(-1.0),topWall(1.0),bottomWall(-1.0),farWall(-1.0){

}

double Corridor::getRW() const{
	return rightWall;
}

double Corridor::getLW() const{
	return leftWall;
}

double Corridor::getTW() const{
	return topWall;
}

double Corridor::getBW() const{
	return bottomWall;
}

double Corridor::getFW() const{
	return farWall;
}
