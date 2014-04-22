/*
* VRPNClient.cpp 
* Project: Virtual Wall
* Author: VR wall
*
* Connect and get data from the VRPN Server
*/

#include "vrpn_Tracker.h"
#include "../Header Files/VRPNClient.h"
#include <iostream>

using namespace std;

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
void VRPNClient :: connectToServer( const char * trackable){
	vrpnTracker = new vrpn_Tracker_Remote(trackable);
	vrpnTracker->register_change_handler(0, vrpnCallback);
}

//Enable callback when you want to read the data
void VRPNClient :: readData(){
	vrpnTracker->mainloop();
	x_coordinate = x_coordinate_;
	y_coordinate = y_coordinate_;
	z_coordinate = z_coordinate_;
}


double VRPNClient :: getXData(){
	return x_coordinate;
}


double VRPNClient :: getYData(){
	return y_coordinate;
}


double VRPNClient :: getZData(){
	return z_coordinate;
}

//Destructor
VRPNClient :: ~VRPNClient(){
	
}
