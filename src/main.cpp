

#include <iostream>
#include <atomic>
#include <thread>

#include "main.hpp"

/// Things to work on if we get time
/**
	- Memory barriers (for atomics and synchronization)
	- Graphics (doubt we will have time) (procrastinators unite tmr)
	
**/

std::atomic_bool FireKey; // This global variable starts
// and stops the Fire state
std::atomic_bool IRon; // This global variable turns on 
// when the a person is walking into an elevator
std::atomic_bool Sound;

std::atomic_bool gStop;
std::atomic_bool gStart{ false };

Controller gControl;
Elevator gLift; // Elevator object
Memory gMem;
Clock gClk;

void output();
void printer();

int main() {
	using std::clog;
	using std::endl;
	using std::cout;
	
	FireKey = false;
	IRon = false;
	Sound = false;
	gStop = false;
	
	// Scenario 1:
	// T = 0s: 
	//   - The elevator is on the 1st floor at 09:00. A student calls the elevator down to Ground.
	// T = 15:
	//   - The student is already in the elevator and presses the 2ndfloor button. 
	//     When the person gets out of the elevator on the 2ndfloor, 
	//     no one gets in and the elevator moves to the default position.
	
	std::thread ptr{ printer };
	cout << "Running Sim 1" << endl;
	
	gClk.reset(9, 0);
	gLift.reset(F1);
	gMem.setFloor(FG);
	gStart = true;
	
	std::this_thread::sleep_for(15s);
	
	gMem.setFloor(F2);
	
	// cout << "Running Sim 2" << endl;
	// gClk.reset(14, 59);
	// gLift.reset(F1);
	
	// exit(0);
	
	while (!gStop)
		;
	
}

void printer() {
	using std::cout;
	using std::endl;
	
	while (!gStart)
		;
	
	for (int i = 0; true; ++i) {
		cout << "At time = " << i << endl;
		output();
		std::this_thread::sleep_for(1s);
	}
}


void output() {
	using std::cout;
	using std::endl;
	
	cout << "Elevator Floor: " << std::to_string(static_cast<int>(gLift.mFloor)) << endl;
	cout << "Elevator State: " << pretty(gLift.mState) << endl;
	cout << "Elevator Stop: " << gLift.mStop << endl;
	cout << "Door State: " << pretty(gLift.mDoor.mState) << endl;
	
	
}