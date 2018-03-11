

#include <iostream>

/// Things to work on if we get time
/**
	- Memory barriers (for atomics and synchronization)
	- Graphics (doubt we will have time) (procrastinators unite tmr)
	
**/

std::atomic_bool FireKey = false; // This global variable starts
// and stops the Fire state
std::atomic_bool IRon = false; // This global variable turns on 
// when the a person is walking into an elevator
std::atomic_bool Sound = false;

Elevator gLift; // Elevator object
Controller gControl;
Memory gMem;
Clock gClk;

int main() {
	// Scenario 1:
	// T = 0s: 
	//   - The elevator is on the 1st floor at 09:00. A student calls the elevator down to Ground.
	// T = 15:
	//   - The student is already in the elevator and presses the 2ndfloor button. 
	//     When the person gets out of the elevator on the 2ndfloor, 
	//     no one gets in and the elevator moves to the default position.
	
	gClk.reset(9, 0);
	gLift.reset(F1);
	// Set the hour and start the gLift
	output();
	
	gMem.setFloor(FG);
	
	output();
	
	std::this_thread::sleep_for(15s);
	gMem.setFloor(F2);
	
}