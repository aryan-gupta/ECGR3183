

#include <iostream>

FloorNum Elevator::getCurrentFloor() {
	return mFloor;
}

void changeState(ElevState newState) {
	mState = newState;
}

