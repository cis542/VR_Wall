/*
* 
* Project: VR Wall
* Author: Jing, Aditya
* main.cpp 
*      
*/

#include "../Header Files/Game.h"
#include <string>

using namespace std;

int main(int argc, char **argv)
{
   const string bluetoothAddr = "00:17:AB:39:4E:C5";
   const string wandAddr = "Wand@158.130.62.115:3883";
   Game Djenga;
   Djenga.connectToInputs(bluetoothAddr, wandAddr);	   
   Djenga.startGame();	    
   return 0;

}
	

