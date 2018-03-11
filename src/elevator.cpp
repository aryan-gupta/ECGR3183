
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
		if (mState == ES_UP) {
			mFloor++;
			
			std::this_thread::sleep_for(5s);
			continue;
		}
		
		if (mState == ES_DOWN) {
			mFloor--;
			
			std::this_thread::sleep_for(5s);
			continue;
		} 
		
		if (mStop and mState == ES_WAIT) {
			//std::cout << "HEre" << std::endl;
			mDoor.start();
		}
	}
	
	std::cout << "Elevator exiting" << std::endl;
}

void Elevator::reset(FloorNum flr) {
	mState = ES_WAIT;
	mFloor = flr;
}