
#include "main.hpp"

Elevator::Elevator() {
	mStop = false;
	mState = ES_WAIT;
	mThread = std::thread{&start, this};
}

Elevator::~Elevator() {
	mThread.join();
}

void Elevator::start() {
	while (!gStart)
		;
	
	while (!gStop) {
		if (mStop) {
			mDoor.start();
		}
		
		if (mState == ES_UP) {
			inc(mFloor);
			
			std::this_thread::sleep_for(5s);
			continue;
		}
		
		if (mState == ES_DOWN) {
			dec(mFloor);
			
			std::this_thread::sleep_for(5s);
			continue;
		} 
	}
	
	std::cout << "Elevator exiting" << std::endl;
}

void Elevator::reset(FloorNum flr) {
	mState = ES_WAIT;
	mFloor = flr;
}