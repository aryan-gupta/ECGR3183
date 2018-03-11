

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

Elevator gLift; // Elevator object
Controller gControl;
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
	std::clog << "At time = 0-" << endl;
	output();
	
	gMem.setFloor(FG);
	
	clog << "At time = 0+" << endl;
	output();
	
	std::this_thread::sleep_for(15s);
	
	clog << "At time = 15-" << endl;
	output();
	
	gMem.setFloor(F2);
	
	clog << "At time = 15+" << endl;
	output();
	
	clog << "Waiting for 10s" << endl;
	std::this_thread::sleep_for(10s);
	
	clog << "At time = 25" << endl;
	output();
	
	for (int i = 25; i < 31; ++i) {
		clog << "At time = " << i << endl;
		std::this_thread::sleep_for(1s);
		output();
	}
	
	
	
}


void output() {
	using std::clog;
	using std::endl;
	
	clog << "Elevator Floor: " << std::to_string(static_cast<int>(gLift.mFloor)) << endl;
	
	
}