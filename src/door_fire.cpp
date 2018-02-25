
#include <iostream>

enum class DoorFireState {
	DOOR_CLOSED = 0b00;
	DOOR_LAT_SND;
	DOOR_OPEN;
	DOOR_CLOSE;
};

class DoorFire {
	DoorFireState mState;
	void latchAndSound(); // This will wait for latching then will output the sound signal after 1s
	void signalDoorOpen();
	void signalDoorClosed();
	
public: 
	void startFSM();
	void receiveOpenDoor();
	void receiveCloseDoor();
	
};