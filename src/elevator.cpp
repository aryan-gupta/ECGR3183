

#include <iostream>

void Elevator::start() {
	while (!gStop) {
		mState = ES_WAIT;
		if (mNextFloor == mCurrFloor and mStop) { 
			/// We want to start the Door FSM
		}
		
		if (mNextFloor > mCurrFloor) {
			mState = ES_UP;
			
			mCurrFloor++;
			
			std::this_thread::sleep_for(5s);
			continue;
		} else if (mNextFloor < mCurrFloor) {
			mState = ES_DOWN;
			
			mCurrFloor--;
			
			std::this_thread::sleep_for(5s);
			continue;
		} else {
			continue;
		}
	}
}