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
	// no copy / move constructors? no copy/move assignment?
	Vector();
	Vector(double xComponent, double yComponent, double zComponent);
	~Vector();

	// I expect that much more common than adding vectors is += and -=, for which you can avoid making a temporary vector
	// Of course for Vectors a good compiler will optimize out this copy, but you might want to practice...
	Vector operator+ (const Vector& bVec)const;
	Vector operator- (const Vector& bVec)const;
	// what do these mean? document your interface when it's not obvious
	double& operator[](size_t idx);
	double operator[](size_t idx)const;

	void reflectAbout ( const Vector& aVec);
		// why are these not class members?
	friend double scalarProduct (const Vector& aVec, const Vector& bVec);
	friend Vector vectorProduct (const Vector& aVec, const Vector& bVec);
	
};
	

	
	
	


