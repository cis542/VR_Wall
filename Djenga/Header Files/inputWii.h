/*
* 
* Project: VR Wall 
* Author: Aditya
* inputWii.h
*
*/

#include <cwiid.h>
#include <iostream>

using namespace std;

class InputWii{
	cwiid_wiimote_t *wiimote;
	struct cwiid_state wiiState;

	public:
		InputWii();
		~InputWii();
                void connectTo(const string& bluetoothID);
		int GetButtonId(void);
};
	
