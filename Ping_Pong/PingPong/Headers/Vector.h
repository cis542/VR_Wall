/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya 
* Vector.h
*
*
*/
#pragma once

#include <stdlib.h>


class Vector{

	float components[3];

	public:
	
	Vector();
	Vector(float xComponent, float yComponent, float zComponent);
	~Vector();

	Vector operator+ (const Vector& bVec)const;
	Vector operator- (const Vector& bVec)const;
	float& operator[](size_t idx);
	float operator[](size_t idx)const;

	void reflectAbout ( const Vector& aVec);
		
	friend float scalarProduct (const Vector& aVec, const Vector& bVec);
	friend Vector vectorProduct (const Vector& aVec, const Vector& bVec);
	
};
	

	
	
	


