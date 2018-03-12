
#include <thread>
#include "main.hpp"

FloorLights::FloorLights()
: X20{ 0 } {
	mThread = std::thread{&start, this}; // invokes the callable
}

FloorLights::~FloorLights() {
	mThread.join();
}

void FloorLights::start() {
	while (!gStop) { // So while the global variable hasnt told us to stop
		unsigned char newValue = 0;
		
		/// get the state from the elevator
		ElevState eleState = gLift.mState;
		
		/// get current floor from the elevator
		FloorNum eleFloor = gLift.mFloor;
		
		switch (eleState) {
			case ES_WAIT: continue; // if we are waiting then dont shine any lights
				
			case ES_UP: {
				int shift = static_cast<int>(eleFloor);
				newValue |= (0x80 >> shift);
			}
			
			case ES_DOWN: {
				int shift = static_cast<int>(eleFloor);
				newValue |= (0x01 << shift);
			}
		}
		
		X20 = newValue;
	}
}

unsigned char FloorLights::getLights() {
	return X20;
}