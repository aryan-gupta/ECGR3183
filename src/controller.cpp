
#include "main.hpp"

#include <thread>

Controller::Controller() {
	mThread = std::thread{&start, this};
}

Controller::~Controller() {
	mThread.join();
}


void Controller::start() {
	while (!gStart)
		;
	
	while (!gStop) {
		auto floor = gMem.getFloor(); // get the next floor to go to
		
		bool memEmpty = gMem.isEmpty();
		
		// go in that direction
		if (floor > gLift.mFloor)
			gLift.mState = ES_UP;
		if (floor < gLift.mFloor)
			gLift.mState = ES_DOWN;
		
		// Wait for the elevator to get to the floor
		bool fire = false;
		while (gLift.mFloor != floor) {
			if (FireKey) {
				fire = true;
				break;
			}
		}
		
		if (fire) continue;
		
		// set the state to wait
		gLift.mStop = true;
		
		// wait for the door to open
		while (gLift.mDoor.mState == DOOR_CLOSED)
			;
		
		gLift.mStop = false;
		gLift.mState = ES_WAIT;
		
		// because we aren't in the fire state we will close/open
		// the door at instant
		if (!FireKey) {
			gLift.mDoor.mConDoorOpen = true;
			gLift.mDoor.mConDoorClose = true;
		}
		
		// Wit for the door to close
		while (gLift.mDoor.mState != DOOR_CLOSED)
			;
		
		gLift.mDoor.mConDoorOpen = false;
		gLift.mDoor.mConDoorClose = false;
		
		// wait for the person to hit a button if the user doesnt 
		// press a button for 30 secs, we will assume there is no
		// person in the elevator and we will reset to the default
		// floor
		if (memEmpty) {
			auto end = clk::now() + 5s; // FIX THIS IT SHOULD BE 30 SECONDS
			while (clk::now() < end) {
				if (!gMem.isEmpty()) // user pushed a floor button
					break;
			}
		}
		// the loop will continue for 30 seconds, if the user pushes abort
		// button in that time then we break and go to that floor
		// if the loops iterates for 30 seconds the next ask from memory
		// will get the default floor, if the loop never iterates then	
		// the queue is not empty so we want to go to the next floor
	}
	
	std::cout << "Controller exiting" << std::endl;
}