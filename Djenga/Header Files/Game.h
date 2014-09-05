/*
*
* Project: VR Wall
* Author: Jing, Aditya
* Game.h
*
*/

#include <stdio.h>
#include <math.h>
#include <fstream>
#include <GL/glut.h>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <string>

#include "../Header Files/Block.h"
#include "../Header Files/Scene.h"
#include "../Header Files/GlutWindow.h"
#include "../Header Files/VRPNClient.h"
#include "../Header Files/inputWii.h"


class Game{
	
	static float PI;
	static int NUM_BLOCKS;
        GlutWindow win;
        VRPNClient VClient;
        InputWii Wii;
        Scene theScene;
        Block* Blocks;
	vec3 point;

	int alpha;
	
	public:
	Game();
	~Game();
	void Draw();
	void initBlocks();
	void initializeGL();
	void connectToInputs(const string& bluetoothAddr, const string& wandAddr);
	void updateState(int value);
	void startGame();
	void drawBlock(Block& b);
};


