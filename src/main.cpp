

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

int main() {
	
}