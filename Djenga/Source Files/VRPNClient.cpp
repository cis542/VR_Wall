/*
*  
* Project: Virtual Wall
* Author: Aditya
* VRPNClient.cpp
* 
*/

#include "vrpn_Tracker.h"
#include "../Header Files/VRPNClient.h"
#include <iostream>

using namespace std;

// Global needed due to library dependency
double x_coordinate_;
double y_coordinate_;
double z_coordinate_;



// Callback when the vrpn client receives new data
void VRPN_CALLBACK vrpnCallback(void* userData, const vrpn_TRACKERCB t ){
	x_coordinate_ = t.pos[0];
	y_coordinate_ = t.pos[1];
	z_coordinate_ = t.pos[2];
}



//Constructor
VRPNClient :: VRPNClient() {
}


//Connect to the server
//Requires the name of the trackable with the IP address and the port number
void VRPNClient :: connectToServer( const string& trackable){
	vrpnTracker = new vrpn_Tracker_Remote(trackable.c_str());
	vrpnTracker->register_change_handler(0, vrpnCallback);
}



//Enable callback when you want to read the data
void VRPNClient :: readData(){
	vrpnTracker->mainloop();
	x_coordinate = x_coordinate_;
	y_coordinate = y_coordinate_;
	z_coordinate = z_coordinate_;
}


//get the x coordinate of the wand
double VRPNClient :: getXData() const{
	return x_coordinate;
}

//get the y coordinate of the wand
double VRPNClient :: getYData() const{
	return y_coordinate;
}

//get the z coordinate of the wand
double VRPNClient :: getZData() const{
	return z_coordinate;
}

//Destructor
VRPNClient :: ~VRPNClient(){
	delete vrpnTracker;	
}
