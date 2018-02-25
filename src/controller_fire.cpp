
#include <iostream>

enum class ControllerState {
	CTR_PAUSED = 0b00;
	CTR_UP;
	CTR_DOWN;
	CTR_WAIT_LATCH;
	CTR_WAIT_DOPEN;
	CTR_WAIT_DCLOSE;
	
	CTR_DC1 = 0b110;
	CTR_DC2;
};

class controller {
	ControllerState mState;
	
public:
	void control();
	
	void signalElevReached();
	void signalDoorClosed();
	void signalDoorOpen();
	void signalLatched() {
		if (mState == CTR_WAIT_LATCH)
			mState = CTR_REPLY;
	}
	
};