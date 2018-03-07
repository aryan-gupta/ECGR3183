
#include <iostream>
#include <chrono>
using namespace clk = std::chrono; // I am not typeing all that over and over

enum class FloorNum {
	FG = 0; 
	F1; 
	F2;
	F3;
};

enum class ElevState {
	ES_WAIT = 0b00;
	ES_DOWN = 0b01;
	ES_UP = 0b10;
	ES_DC = 0b11; // wont be used (dont care)
};

class Elevator {
	FloorNum mFloor;
	ElevState mState;
	
	clk::time_point; // this keeps track of when our last state changed
	
	void startDoorFSM();
	
public:
	FloorNum getFloor();
	ElevState getState();
	void changeState(ElevState newstate);
	
};