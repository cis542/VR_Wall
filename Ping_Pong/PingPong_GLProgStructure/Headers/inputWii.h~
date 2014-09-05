/*
* 
* Project: VR Wall 
* Game: Ping Pong
* Author: Aditya
* inputWii.h
*
*/

#include <cwiid.h>
#include <string>

class InputWii{
	cwiid_wiimote_t *wiimote;
	struct cwiid_state wiiState;

	public:
		InputWii();
		~InputWii();
                void connectTo(const std::string& bluetoothID);
		int GetButtonId(void);
};
	
