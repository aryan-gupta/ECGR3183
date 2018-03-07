
#include <>

FloorLights::FloorLights()
: X20{ 0 } {
	mThread = std::thread{*this}; // invokes the callable
}

void FloorLights::operator() () {
	while (!gStop) { // So while the global variable hasnt told us to stop
		std::byte newValue = 0;
		
		/// get the state from the elevator
		auto eleState = //Elevator::getState();
		
		/// get current floor from the elevator
		auto eleFloor = //Elevator::getFloor();
		
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
		
		X20.load(newValue);
	}
}

std::byte FloorLights::getLights() {
	return X20;
}