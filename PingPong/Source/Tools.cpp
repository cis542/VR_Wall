/*
*
* Ping Pong
* Author: Aditya
* Tools.cpp
*
*
*/

#include "../Headers/Tools.h"

Sphere::Sphere(double r, Vector v, Vector p):radius(r),velocity(v),position(p){

}

Sphere::~Sphere(){

}

void Sphere::setPosition(Vector& pos){
	position = pos;
	
}

void Sphere::updatePosition(double dt){

	position[0] = position[0] + velocity[0]*dt/1000;
	position[1] = position[1] + velocity[1]*dt/1000;
	position[2] = position[2] + velocity[2]*dt/1000;
	
}
void Sphere::setVelocity(Vector& vel){
	velocity = vel;
}

Vector Sphere::getPosition () const{
	return position;
}

Vector Sphere::getVelocity() const{
	return velocity;
}

double Sphere::getRadius() const{
	return radius;
}

Pad::Pad(): position(Vector(0,0,2)),radius(0.1){

}

void Pad::updatePadPosition(Vector& pos){
	position = pos;
}

double Pad::getRadius() const{
	return radius;
}


void Pad::setRadius(double r){
	radius = r;
}

Vector Pad::getPadPosition() const{
	return position;
}


Vector isColliding(const Sphere&s, const Corridor& cor){

	Vector retVal = s.getVelocity();
	Vector spherePosition = s.getPosition();
	Vector temp;

	if (pow((spherePosition[0] - cor.getLW()),2) < pow((s.getRadius()),2)){
		temp = Vector(-1,0,0);
		retVal.reflectAbout(temp);
	}
	else if ( pow((cor.getRW() - spherePosition[0]),2) < pow((s.getRadius()),2)){
		temp = Vector(1,0,0);
		retVal.reflectAbout(temp);
	} 
	else if ( pow((cor.getTW() - spherePosition[1]),2) < pow((s.getRadius()),2)){
		temp = Vector(0,-1,0);
		retVal.reflectAbout(temp);
	}
	else if (pow((spherePosition[1] - cor.getBW()),2) < pow((s.getRadius()),2)){
		temp = Vector(0,1,0);
		retVal.reflectAbout(temp);
	}
	else if (pow((spherePosition[2] - cor.getFW()),2) < pow((s.getRadius()),2)){
		temp = Vector(0,0,1);
		retVal.reflectAbout(temp);
	}
	
	return retVal;
}	

Vector isCollidingWithPad(const Sphere&s, const Pad& p){

	Vector retVal = s.getVelocity();
	Vector spherePosition = s.getPosition();
	Vector padPosition = p.getPadPosition();
	Vector temp;

	double total_dist = pow(padPosition[0]-spherePosition[0],2)+pow(padPosition[1]-spherePosition[1],2) + pow(padPosition[2]-spherePosition[2],2);
	total_dist = pow(total_dist, 0.5);

	double dist = pow(padPosition[0]-spherePosition[0],2)+pow(padPosition[1]-spherePosition[1],2);
	dist = pow(dist,0.5);

	double barrier = pow(s.getRadius(),2) + pow(p.getRadius(),2) + s.getRadius()*p.getRadius()*(dist-p.getRadius())/s.getRadius();
	barrier = pow(barrier,0.5);
	
	if (dist < p.getRadius()){
		if (padPosition[2] - spherePosition[2] < s.getRadius()){
			temp = Vector(0,0,-1);
			retVal.reflectAbout(temp);
		}
	}
	else if ( total_dist < barrier && padPosition[2] - spherePosition[2] < s.getRadius()){
		if (padPosition[2] - spherePosition[2] < s.getRadius()){
			double x_diff = spherePosition[0] - padPosition[0];
			double y_diff = spherePosition[1] - padPosition[1];
			double z_diff = spherePosition[2] - padPosition[2];
			double s1 = pow(x_diff,2) + pow(y_diff,2);
			s1 = pow(s1,0.5);
				
			x_diff = spherePosition[0] - (padPosition[0] + p.getRadius()*x_diff/s1);
			y_diff = spherePosition[1] - (padPosition[1] + p.getRadius()*y_diff/s1);

				
			double s = pow(x_diff,2) + pow(y_diff,2) + pow(z_diff,2);
			s = pow(s,0.5);
			temp[0] = x_diff/s;
			temp[1] = y_diff/s;
			temp[2] = z_diff/s;
				
			retVal.reflectAbout(temp);
				
		}
	}
	

	return retVal;
}

void drawSphere(const Sphere& s){
	int i,j;
	int lats = 100;
	int longs = 100;
	Vector center = s.getPosition();
	double rad = s.getRadius();
	
	for (i=0;i<= lats;i++){
		double lat0 = M_PI*(-0.5 + (double)(i-1)/lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);
		
		double lat1 = M_PI*(-0.5 + (double)i/lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++){
			double lng = 2*M_PI*(double)(j-1)/longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(-center[0] + rad*x*zr0, center[1] + rad*y*zr0,center[2] +  rad*z0);
			glVertex3f(-center[0] + rad*x*zr0, center[1] + rad*y*zr0,center[2] +  rad*z0);
			glNormal3f(-center[0] + rad*x*zr1, center[1] + rad*y*zr1,center[2] +  rad*z1);
			glVertex3f(-center[0] + rad*x*zr1, center[1] + rad*y*zr1,center[2] +  rad*z1);
		}
		glEnd();
	}
}



	

