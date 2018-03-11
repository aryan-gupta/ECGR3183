#pragma once

enum IRState {
	IR_OFF = 0b00,
	IR_BUSY,
	IR_CLEAR,
	IR_DONE
	
};

struct IR_Sensor {
	IRState mState;
	
	void start();	
};