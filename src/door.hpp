
#include <iostream>

enum class DoorState {
	DOOR_CLOSED = 0b000;
	DOOR_LAT_SND;
	DOOR_OPEN;
	DOOR_IR;
	DOOR_CLOSING;
	DOOR_DC1 = 0b101; // not needed, just so we can remember
	DOOR_DC2;
	DOOR_DC3;
};

struct Door {
	DoorState mState;
	IR_Sensor mIRSen;
	
	std::atomic_bool mConDoorOpen;
	std::atomic_bool mConDoorClose;
	
	void start();
	
};