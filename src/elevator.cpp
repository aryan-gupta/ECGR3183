

#include <iostream>

void Elevator::start() {
	while (!gStop) {
		if (mState == ES_UP) {
			mFloor++;
			
			std::this_thread::sleep_for(5s);
			continue;
		}
		
		if (mState == ES_DOWN) {
			mFloor--;
			
			std::this_thread::sleep_for(5s);
			continue;
		} else {
			mDoor.start();
		}
	}
}

void Elevator::reset(FloorNum flr) {
	mState = ES_WAIT;
	mFloor = flr;
}