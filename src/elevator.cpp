
#include <iostream>

enum class FloorNum {
	FG = 0; 
	F1; 
	F2;
	F3;
};

enum class ElevState {
	ES_WAIT = 0b00;
	ES_DOWN = 0b01;
	ES_UP = 0b10;
	ES_DC = 0b11; // wont be used (dont care)
};

class elevator {
	FloorNum mFloor;
	ElevState mState
	
	void startDoorFSM();
	
public:
	FloorNum getCurrentFloor();
	void changeState(ElevState newstate);
	
};