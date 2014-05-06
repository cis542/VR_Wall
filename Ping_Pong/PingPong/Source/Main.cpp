/*
*
* Project: VR Wall
* Game: Ping Pong
* Author: Aditya
* Main.cpp
*
*
*/


#include "../Headers/Game.h"
#include <string>


int main(int argc, char **argv)
{
   glutInit(&argc,argv);
   const std::string bluetoothAddr = "00:17:AB:39:4E:C5";
   const std::string wandAddr = "Wand@158.130.62.115:3883";
   Game PingPong;
   PingPong.connectToInputs(bluetoothAddr, wandAddr);	   
   PingPong.startGame();	    
   return 0;

}
