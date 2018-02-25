

enum class IRState {
	IR_OFF = 0b00;
	IR_BUSY;
	IR_CLEAR;
	IR_DONE;
	
};

class ir_sensor {
	IRState mState;
	void signalDoorClose();
	
public:
	void startIRSensor();
	void receiveFireOn();
	void IRon();
	
};