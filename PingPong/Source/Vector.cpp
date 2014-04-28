/*
*
* 
* Vector.cpp
*
*
*/
#include "../Headers/Vector.h"

Vector::Vector():components({0}){

}

Vector::Vector(double xComponent, double yComponent, double zComponent):components({xComponent, yComponent, zComponent}){
	
}

Vector Vector::operator+ (const Vector& bVec)const{
	
	Vector temp;
	temp[0] = components[0] + bVec[0];
	temp[1] = components[1] + bVec[1];
	temp[2] = components[2] + bVec[2];

	return temp;
}

Vector Vector::operator- (const Vector& bVec)const{
	
	Vector temp;
	temp[0] = components[0] - bVec[0];
	temp[1] = components[1] - bVec[1];
	temp[2] = components[2] - bVec[2];

	return temp;
}

double& Vector::operator[](size_t idx){
	
	return components[idx];
}


double Vector::operator[](size_t idx)const{
	
	return components[idx];
}	


void Vector::reflectAbout (const Vector& aVec){
	double alpha;	
	alpha = -2 * scalarProduct(*this, aVec);
	components[0] = alpha * aVec[0] + components[0];
	components[1] = alpha * aVec[1] + components[1];
	components[2] = alpha * aVec[2] + components[2]; 
}
	
double scalarProduct( const Vector& aVec, const Vector& bVec){
	
	double retVal;
	retVal = aVec[0]*bVec[0] + aVec[1]*bVec[1] + aVec[2]*bVec[2];
	
	return retVal;
}

Vector vectorProduct ( const Vector& aVec, const Vector& bVec){

	Vector temp;
	temp[0] =  (aVec[1]*bVec[2] - aVec[2]*bVec[1]);
	temp[1] = -(aVec[0]*bVec[2] - aVec[2]*bVec[0]);
	temp[2] =  (aVec[0]*bVec[1] - aVec[1]*bVec[0]);

	return temp;
}	
	

Vector::~Vector(){

}
