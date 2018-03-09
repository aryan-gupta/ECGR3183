
#include <iostream>
#include <chrono>
using namespace clk = std::chrono; // I am not typeing all that over and over

enum class FloorNum {
	FG = 0; 
	F1; 
	F2;
	F3;
};

class invalid_floor_reached : public std::exception {
public:
	std::string what() {
		return "Umm, ya you killed people. Invalid floor reached";
	}
}

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

enum class ElevState {
	ES_WAIT = 0b00;
	ES_DOWN = 0b01;
	ES_UP = 0b10;
	ES_DC = 0b11; // wont be used (dont care)
};

class Elevator {
	FloorNum mCurrFloor;
	FloorNum mNextFloor;
	ElevState mState;
	Door mDoor;
	std::atomic_bool 
	
	clk::time_point; // this keeps track of when our last state changed
	
	void startDoorFSM();
	
public:
	FloorNum getFloor();
	ElevState getState();
	void changeState(ElevState newstate);
	void start();
	
};