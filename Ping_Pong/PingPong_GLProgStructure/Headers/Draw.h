/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Draw.h
*
*/

#pragma once
#include <GL/gl.h>
#include <GL/glut.h>
#include "Sphere.h"
#include "Pad.h"
#include "Corridor.h"


void drawPad(Pad& p);
void drawSphere(const Sphere& s);
void drawCorridor();

