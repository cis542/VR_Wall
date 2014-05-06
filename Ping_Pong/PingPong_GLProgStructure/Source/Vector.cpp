/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Vector.cpp
*
*/

#include "../Headers/Vector.h"

Vector::Vector():components({0}){

}

Vector::Vector(float xComponent, float yComponent, float zComponent):components({xComponent, yComponent, zComponent}){
	
}

// Addition of two vectors
Vector Vector::operator+ (const Vector& bVec)const{
	
	Vector temp;
	temp[0] = components[0] + bVec[0];
	temp[1] = components[1] + bVec[1];
	temp[2] = components[2] + bVec[2];

	return temp;
}

// Subtraction of Vectors
Vector Vector::operator- (const Vector& bVec)const{
	
	Vector temp;
	temp[0] = components[0] - bVec[0];
	temp[1] = components[1] - bVec[1];
	temp[2] = components[2] - bVec[2];

	return temp;
}

float& Vector::operator[](size_t idx){
	
	return components[idx];
}


float Vector::operator[](size_t idx)const{
	
	return components[idx];
}	

// Reflects a vector about aVec
// Ensures that the Angle of Incidence = Angle of Reflection
void Vector::reflectAbout (const Vector& aVec){
	float alpha;	
	alpha = -2 * scalarProduct(*this, aVec);
	components[0] = alpha * aVec[0] + components[0];
	components[1] = alpha * aVec[1] + components[1];
	components[2] = alpha * aVec[2] + components[2]; 
}


// Returns the scalar product of two vectors	
float scalarProduct( const Vector& aVec, const Vector& bVec){
	
	float retVal;
	retVal = aVec[0]*bVec[0] + aVec[1]*bVec[1] + aVec[2]*bVec[2];
	
	return retVal;
}

// Returns the vector product of two vectors
Vector vectorProduct ( const Vector& aVec, const Vector& bVec){

	Vector temp;
	temp[0] =  (aVec[1]*bVec[2] - aVec[2]*bVec[1]);
	temp[1] = -(aVec[0]*bVec[2] - aVec[2]*bVec[0]);
	temp[2] =  (aVec[0]*bVec[1] - aVec[1]*bVec[0]);

	return temp;
}	
	

Vector::~Vector(){

}
