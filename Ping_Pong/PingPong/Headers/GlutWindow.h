/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* GlutWindow.h
*
*
*/
#pragma once

#include <string>


class GlutWindow{
   int width;
   int height;
   std::string title;
   float fieldOfViewAngle;
   float z_near;
   float z_far;
   public:
      GlutWindow(int w, int h, const std::string s, float fov, float zn, float zf): width(w),height(h),title(s),fieldOfViewAngle(fov),z_near(zn),z_far(zf){
      }
      int getWidth() const{
	return width;
      }
	int getHeight() const{
	return height;
      }
	std::string getTitle() const{
	return title;
      }
	float getFOVA() const{
	return fieldOfViewAngle;
      }
	float getZNear() const{
	return z_near;
      }
	float getZFar() const{
	return z_far;
      }
	void setWidth(int w){
	   width = w;
      }
	void setHeight(int h){
	   height = h;
      }
	void setTitle(const std::string& s){
	   title = s;
      }
	void setFOVA(float a) {
	   fieldOfViewAngle = a;
      }
	void setZNear(float zn) {
	   z_near = zn;
      }
	void setZFar(float zf){
	   z_far = zf;
      }
  
};

