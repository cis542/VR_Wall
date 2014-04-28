/*
*
* 
* Vector.h
*
*
*/
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>


using namespace std;
class Vector{

	double components[3];

	public:
	
	Vector();
	Vector(double xComponent, double yComponent, double zComponent);
	~Vector();

	Vector operator+ (const Vector& bVec)const;
	Vector operator- (const Vector& bVec)const;
	double& operator[](size_t idx);
	double operator[](size_t idx)const;

	void reflectAbout ( const Vector& aVec);
		
	friend double scalarProduct (const Vector& aVec, const Vector& bVec);
	friend Vector vectorProduct (const Vector& aVec, const Vector& bVec);
	
};
	

	
	
	


