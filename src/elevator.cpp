

#include <iostream>

void Elevator::start() {
	while (!gStop) {
		if (mState == ES_UP) {
			mCurrFloor++;
			
			std::this_thread::sleep_for(5s);
			continue;
		}
		
		if (mState == ES_DOWN) {
			mCurrFloor--;
			
			std::this_thread::sleep_for(5s);
			continue;
		} else {
			mDoor.start();
		}
	}
}