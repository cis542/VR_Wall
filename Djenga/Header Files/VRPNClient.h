#include "vrpn_Tracker.h"
#include <iostream>

using namespace std;

class VRPNClient{
	public:
	vrpn_Tracker_Remote* vrpnTracker;
	double x_coordinate;
	double y_coordinate;
	double z_coordinate;

	
	VRPNClient();
	virtual ~VRPNClient();
	virtual void connectToServer(const char * trackable);
	virtual void readData();
	virtual double getXData();
	virtual double getYData();
	virtual double getZData();
};


