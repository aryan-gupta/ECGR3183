#pragma once

#include <iostream>
#include <chrono>

#include "door.hpp"

enum FloorNum {
	FG = 0,
	F1,
	F2,
	F3
};

class invalid_floor_reached : public std::exception {
public:
	std::string what() {
		return "Umm, ya you killed people. Invalid floor reached";
	}
};

/// I know I know What am I doing here, Do I even know C++.
/// Ill fix it later
inline void operator++ (FloorNum& a) {
	switch (a) {
		case FG: a = F1; return;
		case F1: a = F2; return;
		case F2: a = F3; return;
		default:         throw invalid_floor_reached();
	}
}

inline void operator++ (FloorNum& a, int) {
	switch (a) {
		case FG: a = F1; return;
		case F1: a = F2; return;
		case F2: a = F3; return;
		default:         throw invalid_floor_reached();
	}
}

inline void operator-- (FloorNum& a) {
	switch (a) {
		case F1: a = FG; return;
		case F2: a = F1; return;
		case F3: a = F2; return;
		default:         throw invalid_floor_reached();
	}
}

inline void operator-- (FloorNum& a, int) {
	switch (a) {
		case F1: a = FG; return;
		case F2: a = F1; return;
		case F3: a = F2; return;
		default:         throw invalid_floor_reached();
	}
}

enum ElevState {
	ES_WAIT = 0b00,
	ES_DOWN = 0b01,
	ES_UP = 0b10,
	ES_DC = 0b11 // wont be used (dont care)
};

inline std::string pretty(ElevState s) {
	switch (s) {
		case ES_WAIT:
			return "Waiting";
		case ES_DOWN:
			return "Down";
		case ES_UP:
			return "Up";
		default:
			return "Broken";
	}
}

struct Elevator {
	FloorNum mFloor;
	ElevState mState;
	Door mDoor;
	std::thread mThread;
	
	std::atomic_bool mStop;
	
	Elevator();
	~Elevator();
	
	void start();
	void reset(FloorNum flr);
	
};