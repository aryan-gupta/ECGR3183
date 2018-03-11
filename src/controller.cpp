

void Controller::start() {
	while (true) {
		auto floor = // memory.getfloor();
		
		if (floor > gLift.mCurrFloor)
			gLift.mState = ES_UP;
		if (floor < gLift.mCurrFloor)
			gLift.mState = ES_DOWN;
		
		while (gLift.mCurrFloor != floor)
			;
		
		gLift.mState = ES_WAIT;
		
		while (gLift.mDoor.mState != DOOR_CLOSED)
			;
		
		gLift.mDoor.mConDoorOpen = true;
		
		gLift.mDoor.mConDoorClose = true; 
		
		while (gLift.mDoor.mState != DOOR_CLOSED)
			;
		
		
		
	}
}