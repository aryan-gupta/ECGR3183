

enum class IRState {
	IR_OFF = 0b00;
	IR_BUSY;
	IR_CLEAR;
	IR_DONE;
	
};

class IR_Sensor {
	IRState mState;
	void signalDoorClose();
	
public:
	void start();
	void receiveFireOn();
	void IRon();
	
};