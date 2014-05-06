/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Game.h
*
*/

#pragma once

#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <string>


#include "../Headers/Sphere.h"
#include "../Headers/Pad.h"
#include "../Headers/Corridor.h"
#include "../Headers/GlutWindow.h"
#include "../Headers/VRPNClient.h"
#include "../Headers/inputWii.h"



class Game{
	
	static float alpha;    // to convert from the camera frame of reference to the GL frame of reference

	GlutWindow win;        
        VRPNClient VClient;
        InputWii Wii;
        Sphere ball;
	Pad pad;
	Corridor cor;

	
	public:
	Game();
	~Game();

	void drawPad(Pad& p)const;
	void drawSphere(const Sphere& s)const;
	void drawCorridor() const;

	void initializeGL();
	void connectToInputs(const std::string& bluetoothAddr, const std::string& wandAddr);
	void updateState(int value);
	void startGame();
	void Draw();
	
	Vector isCollidingWithWall(const Sphere& s, const Corridor& cor);	
	Vector isCollidingWithPad(const Sphere& s, const Pad& p);

};


