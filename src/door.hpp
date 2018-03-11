#pragma once

#include <atomic>

#include "ir_sensor.hpp"

enum DoorState {
	DOOR_CLOSED = 0b000,
	DOOR_LAT_SND,
	DOOR_OPEN,
	DOOR_IR,
	DOOR_CLOSING,
	DOOR_DC1 = 0b101, // not needed, just so we can remember
	DOOR_DC2,
	DOOR_DC3
};

inline std::string pretty(DoorState s) {
	switch (s) {
		case DOOR_CLOSED:
			return "Closed";
		case DOOR_LAT_SND:
			return "Latch and Sound";
		case DOOR_OPEN:
			return "Open";
		case DOOR_IR:
			return "Waiting for IR";
		case DOOR_CLOSING:
			return "Door Closing";
			
		default:
			return "Broken";
	}
}

struct Door {
	DoorState mState;
	IR_Sensor mIRSen;
	
	std::atomic_bool mConDoorOpen;
	std::atomic_bool mConDoorClose;
	
	void start();
	
};