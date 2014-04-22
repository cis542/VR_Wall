/*
* inputWii.h
*
* Author: VR wall
*
*
*/

#include <cwiid.h>
#include <iostream>

using namespace std;

class InputWii{
	cwiid_wiimote_t *wiimote;
	struct cwiid_state wiiState;

	public:
		InputWii(const char * BluetoothID);
		virtual int GetButtonId(void);
};
	
