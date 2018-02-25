
#include <iostream>

enum class DoorState {
	DOOR_CLOSED = 0b000;
	DOOR_LAT_SND;
	DOOR_OPEN;
	DOOR_IR;
	DOOR_CLOSE;
	DOOR_DC1 = 0b101; // not needed, just so we can remember
	DOOR_DC2;
	DOOR_DC3;
};

class Door {
	DoorState mState;
	void latchAndSound(); // This will wait for latching then will output the sound signal after 1s
	void startIR();
	void signalDoorClosed();
	
public:
	void startFSM();
	void receiveControllerDoorOpen();
	void receiveIRend();
	void closeDoor();
	
};