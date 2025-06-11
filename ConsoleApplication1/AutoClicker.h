/*
* Auto Clicker header file
* 
* @author Spencer Cologna
* @version 6/6/2025
*/

#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

class AutoClicker {
private:
	bool isActive;
	
	/*
	* Method for switching the active state from on to off or vice versa
	*/
	void switchActive();


public:
	/*
	* Constructor for the auto clicker
	*/
	AutoClicker();

	/*
	* Runs the Auto Clicker by using the winuser sendinput function
	*/
	void autoClick();
};

#endif
