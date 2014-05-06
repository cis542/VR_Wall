#include "Corridor.h"

Corridor::Corridor():leftWall(-5.0),rightWall(5.0),topWall(5.0f),bottomWall(-5.0f),farWall(-32.0f){

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
