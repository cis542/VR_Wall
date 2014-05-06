/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Collision.h
*
*/

#pragma once

#include "Sphere.h"
#include "Pad.h"
#include "Corridor.h"

Vector isCollidingWithWall(const Sphere&s, const Corridor& cor);
Vector isCollidingWithPad(const Sphere&s, const Pad& p);

