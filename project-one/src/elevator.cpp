
#include "main.hpp"

Elevator::Elevator()
: mState{ ES_WAIT }, mStop{ false } {
	mThread = std::thread{&start, this};
}

Elevator::~Elevator() {
	mThread.join();
}

void Elevator::start() {
	while (!gStart) // Wait for all go signal
		;
	
	while (!gStop) {
		if (mStop) { // Controller wants us to stop at this foor
			mDoor.start();
		}
		
		if (mState == ES_UP) {
			inc(mFloor); // to lazy to change it back to ++/--
			
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