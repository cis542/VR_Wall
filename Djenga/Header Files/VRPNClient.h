/*
*
* Project : VR Wall
* Author: Aditya
* VRPNClient.h
*
*/

#include "vrpn_Tracker.h"
#include <iostream>

using namespace std;

class VRPNClient{
	
	vrpn_Tracker_Remote* vrpnTracker;
	double x_coordinate;
	double y_coordinate;
	double z_coordinate;

	public:
	VRPNClient();
	~VRPNClient();
	void connectToServer(const string& trackable);
	void readData();
	double getXData() const;
	double getYData() const;
	double getZData() const;
};


