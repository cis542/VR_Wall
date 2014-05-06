/*
*
* Project : VR Wall
* Game: Ping Pong
* Author: Aditya
* VRPNClient.h
*
*/

#include "vrpn_Tracker.h"
#include <string>

class VRPNClient{
	
	vrpn_Tracker_Remote* vrpnTracker;
	float x_coordinate;
	float y_coordinate;
	float z_coordinate;

	public:
	VRPNClient();
	~VRPNClient();
	void connectToServer(const std::string& trackable);
	void readData();
	float getXData() const;
	float getYData() const;
	float getZData() const;
};


