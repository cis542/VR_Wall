/*
* 
* Project : VR Wall
* Author: Aditya
* inputWii.cpp
*
*/

#include <cwiid.h>
#include "../Headers/inputWii.h"

InputWii :: InputWii (){

}

InputWii :: ~InputWii (){
	cwiid_close(wiimote);
}


// Connects to the wiimote at the specified address
// Enable reporting of the button events

void InputWii::connectTo(const std::string& bluetoothID){
	
	bdaddr_t bdaddr;
	str2ba(bluetoothID.c_str(),&bdaddr);
	printf("Put Wiimote L in discoverable mode now (press 1+2)...\n");
	if (!(wiimote = cwiid_open(&bdaddr, CWIID_FLAG_REPEAT_BTN))) {
		fprintf(stderr, "Unable to connect to wiimote\n");
	}
	cwiid_command(wiimote, CWIID_CMD_RPT_MODE,CWIID_RPT_BTN);
}



// Reads the state and returns the id of the button pressed.

int InputWii :: GetButtonId(void) {

	cwiid_get_state(wiimote, &wiiState);
	return wiiState.buttons;
}
