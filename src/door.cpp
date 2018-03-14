
#include "main.hpp"

void Door::start() {
	// We are currently in DOOR_CLOSED state, we will change state and
	// Latch and send sound output
	mState = DOOR_LAT_SND;
	std::this_thread::sleep_for(2s); // wait for 2s to latch
	Sound = true;
	
	// Door is latched now we wait for the controller to tell us to
	// open the gate
	while (!mConDoorOpen) ;// { std::this_thread::yield(); }
	
	// Open Door (Turn off sound too)
	mState = DOOR_OPEN;
	std::this_thread::sleep_for(1s); // Door is opening
	
	// Door is open, now let people in and out
	mState = DOOR_IR; // Honestly this should be called Door Wait
	// but too lazy to change
	Sound = false;
	if (!FireKey) {
		mIRSen.start(); // This is a blocking function
		// this function will start the IRSensor and wait
		// for its finish to close the door
	}
	
	// Wait for the controller to send close door signal
	while (!mConDoorClose) ;// { std::this_thread::yield(); }
	mState = DOOR_CLOSING;
	std::this_thread::sleep_for(1s); // Door is closing
	
	mState = DOOR_CLOSED; // Door is closed 

}