

#include <iostream>

FloorNum Elevator::getCurrentFloor() {
	return mCurrFloor;
}

void Elevator::changeState(ElevState newState) {
	mState = newState;
}

void Elevator::start() {
	while (!gStop) {
		mState = ES_WAIT;
		if (mNextFloor == mCurrFloor and ) { 
			
		}
		
		if (mNextFloor > mCurrFloor) {
			mState = ES_UP;
			
			std::this_thread::sleep_for(5s);
			continue;
		} else if (mNextFloor < mCurrFloor) {
			mState = ES_DOWN;
			std::this_thread::sleep_for(5s);
			
		} else {
			continue;
		}
	}
}