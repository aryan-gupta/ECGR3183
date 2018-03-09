

void Door::latchAndSound() {
	std::this_thread::sleep_for(2s);
	Sound = true;
	// How long is sound going to be on for?
}

void Door::waitIR() {
	mIRSen.start(); // This is a blocking function
	// this function will start the IRSensor and wait
	// for its finish to close the door
	
	// What do we do here after?
}


void Door::start() {
	mState = DOOR_CLOSED;
	
	mState = DOOR_LAT_SND;
	latchAndSound();
	
	mState = DOOR_OPEN;
	while (!mConDoorOpen) { std::this_thread::yield(); }
	// Open Door
	
	mState = DOOR_IR;
	waitIR();
	
	mState = DOOR_CLOSE;
	while (!mConDoorClose) { std::this_thread::yield(); }
	// close door
	
	
}