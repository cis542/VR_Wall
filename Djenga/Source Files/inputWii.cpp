/*
* inputWii.cpp
*
* Author: VR wall
*
*
*/

#include <cwiid.h>
#include "../Header Files/inputWii.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct cwiid_state state;
cwiid_wiimote_t *wiimote;

InputWii :: InputWii (const char* BluetoothID){

	bdaddr_t bdaddr;
	str2ba(BluetoothID,&bdaddr);
	printf("Put Wiimote L in discoverable mode now (press 1+2)...\n");
	if (!(wiimote = cwiid_open(&bdaddr, CWIID_FLAG_REPEAT_BTN))) {
		fprintf(stderr, "Unable to connect to wiimote\n");
		exit(0);
	}
	cwiid_command(wiimote, CWIID_CMD_RPT_MODE,CWIID_RPT_BTN);
}

int InputWii :: GetButtonId(void){

	cwiid_get_state(wiimote, &state);
	return state.buttons;
}
