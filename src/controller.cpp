

void Controller::start() {
	while (true) {
		auto floor = gMem.getFloor(); // get the next floor to go to
		
		bool memEmpty = gMem.isEmpty();
		
		// go in that direction
		if (floor > gLift.mCurrFloor)
			gLift.mState = ES_UP;
		if (floor < gLift.mCurrFloor)
			gLift.mState = ES_DOWN;
		
		// Wait for the elevator to get to the floor
		while (gLift.mCurrFloor != floor)
			;
		// set the state to wait
		gLift.mState = ES_WAIT;
		
		// wait for the door to open
		while (gLift.mDoor.mState != DOOR_CLOSED)
			;
		
		// because we aren't in the fire state we will close/open
		// the door at instant
		gLift.mDoor.mConDoorOpen = true;
		gLift.mDoor.mConDoorClose = true; 
		
		// Wit for the door to close
		while (gLift.mDoor.mState != DOOR_CLOSED)
			;
		
		// wait for the person to hit a button if the user doesnt 
		// press a button for 30 secs, we will assume there is no
		// person in the elevator and we will reset to the default
		// floor
		if (memEmpty)
	}
}