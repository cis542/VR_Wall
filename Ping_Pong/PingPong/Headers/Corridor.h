/*
*
* PingPong
* Author: Aditya
* Corridor.h
*
*
*/

#pragma once


class Corridor{
	
	float rightWall;
	float leftWall;
	float topWall;
	float bottomWall;
	float farWall;
	
	public:
	Corridor();
	float getRW() const;
	float getLW() const;
	float getTW() const;
	float getBW() const;
	float getFW() const;
	
};
