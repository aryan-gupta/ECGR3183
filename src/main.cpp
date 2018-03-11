

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
	
	std::cout << "Running Sim 1" << endl;
	
	gClk.reset(9, 0);
	gLift.reset(F1);
	// Set the hour and start the gLift
	std::cout << "At time = 0-" << endl;
	output();
	
	gStart = true;
	gMem.setFloor(FG);
	
	cout << "At time = 0+" << endl;
	output();
	
	for (int i = 0; i < 15; ++i) {
		std::this_thread::sleep_for(1s);
		cout << "At time = " << i << endl;
		output();
	}
	
	gMem.setFloor(F2);
	
	cout << "At time = 15+" << endl;
	output();
	
	for (int i = 15; i < 101; ++i) {
		std::this_thread::sleep_for(1s);
		cout << "At time = " << i << endl;
		output();
	}
	
	exit(0);
	
}


void output() {
	using std::cout;
	using std::endl;
	
	cout << "Elevator Floor: " << std::to_string(static_cast<int>(gLift.mFloor)) << endl;
	cout << "Elevator State: " << pretty(gLift.mState) << endl;
	
	
	
}