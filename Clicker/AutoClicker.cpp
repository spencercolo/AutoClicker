/**
* AutoClicker definition class
**/

#include "AutoClicker.h"

#define WINVER 0x0500
#include "windows.h"

void AutoClicker::autoClick() {
	//Code from windows.h
	//SendInput????
	INPUT ips[2] = {};
	ips[0].type = INPUT_MOUSE;
	ips[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	ips[1].type = INPUT_MOUSE; 
	ips[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	

	while (isActive) {
		SendInput(2, ips, sizeof(INPUT));
	}
}

void AutoClicker::switchActive() {
	if (isActive)
		isActive = false;
	else isActive = true;

}

AutoClicker::AutoClicker() : isActive(true) {
}
