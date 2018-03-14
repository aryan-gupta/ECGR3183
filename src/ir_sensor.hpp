#pragma once

#include <string>

enum IRState {
	IR_OFF = 0b00,
	IR_BUSY,
	IR_CLEAR,
	IR_DONE
	
};

inline std::string pretty(IRState s) {
	switch (s) {
		case IR_OFF:
			return "Sensor Off";
		case IR_BUSY:
			return "Person Walking";
		case IR_CLEAR:
			return "No Person Walking";
		case IR_DONE:
			return "Sensor Done";
		default:
			return "Laser weapons kill people";
	}
}

struct IR_Sensor {
	IRState mState;
	
	void start();	
};