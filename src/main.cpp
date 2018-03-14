

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
	
	// cout << "Running Sim 1" << endl;
	
	// gClk.reset(9, 0);
	// gLift.reset(F1);
	// gMem.setFloor(FG);
	// gStart = true;
	
	// std::this_thread::sleep_for(15s);
	
	// gMem.setFloor(F2);
	
	
// T = 0: A group of students call the elevator to the 3 rd floor at 14:59 (the elevator is on 1 st ). When it gets
// there, the students take 7 seconds to get into the elevator. One of the students presses the 1 st floor
// button immediately after the doors close. After 2 seconds, another student presses the 2 nd floor button.
// After another 1 second, a third student presses the Ground floor button. After servicing all requests, the
// elevator returns to the default floor.
	// cout << "Running Sim 2" << endl;
	// gClk.reset(14, 59);
	// gLift.reset(F1);
	// gMem.setFloor(F3);
	// gStart = true;
	
	// while (gLift.mFloor != F3)
		// ;
	// IRon = true;
	// while (gLift.mDoor.mState != DOOR_IR)
		// ;
	
	// std::this_thread::sleep_for(7s);
	
	// IRon = false;
	// while (gLift.mDoor.mState != DOOR_CLOSED)
		// ;
	// gMem.setFloor(F1);
	
	// std::this_thread::sleep_for(2s);
	// gMem.setFloor(F2);
	
	// std::this_thread::sleep_for(1s);
	// gMem.setFloor(FG);
	
	
// T = 0: The elevator is on the 2ndfloorat 13:59. A student calls the elevator to the Ground floor.The student 
// takes 3 seconds to get into the elevator and presses the 3rdfloor after 2 seconds after the doors close. When 
// the students comes out of the elevator, another student gets on (assume no additional time is spent, i.e. it 
// takes 0 seconds for him to get in). This student selects the 1stfloor button immediately upon the closing of 
// the doors. 

// When the elevator is at the 2ndfloor location, a firefighter calls the elevator from the Ground floor.
// When the elevator reaches the Ground floor, the firefighter takes 2 seconds to get into the elevator and presses 
// door closing button after 2 seconds after getting into the elevator. The firefighter goes to the 3rdfloor (the 
// student did not disembark, the student’s request to go to the 1stfloor was not fulfilled). When the elevator gets 
// to the 3rdfloor, the firefighter manually opens the door and leaves it open for 5 seconds. The firefighter waits 
// for1 second before closing the door. Once the door is open, the firefighter waits for 1 second and then presses 
// the button to go to the Ground floor. When they reach the Ground floor and the firefighter disembarks, the elevator
// goes out of Firefighter mode and resumes normal operation.
	cout << "Running Sim 3" << endl;
	gClk.reset(13, 59);
	gLift.reset(F2);
	gMem.setFloor(FG);
	
	gStart = true;
	
	while (gLift.mFloor != FG)
		;
	
	IRon = true;
	while (gLift.mDoor.mState != DOOR_IR)
		;
	
	std::this_thread::sleep_for(3s);
	
	IRon = false;
	
	while (gLift.mDoor.mState != DOOR_CLOSED)
		;
	
	std::this_thread::sleep_for(2s);
	
	gMem.setFloor(F3);
	
	while (gLift.mDoor.mState != DOOR_IR)
		;
	
	while (gLift.mDoor.mState != DOOR_CLOSED)
		;
	
	gMem.setFloor(F1);
	
	while (gLift.mFloor != F2)
		;
	
	FireKey = true;
	gMem.setFloor(FG);
	
	while (gLift.mDoor.mState != DOOR_LAT_SND)
		;
	
	gLift.mDoor.mConDoorOpen = true;
	
	while (gLift.mDoor.mState != DOOR_IR)
		;
	
	std::this_thread::sleep_for(4s);
	
	gLift.mDoor.mConDoorClose = true;
	gMem.setFloor(F3);
	
	while (gLift.mDoor.mState != DOOR_LAT_SND)
		;
	
	gLift.mDoor.mConDoorOpen = true;
	
	std::this_thread::sleep_for(6s);
	
	gLift.mDoor.mConDoorClose = true;
	
	while (gLift.mDoor.mState != DOOR_CLOSED)
		;
	
	std::this_thread::sleep_for(1s);
	
	gMem.setFloor(FG);
	
	while (gLift.mDoor.mState != DOOR_LAT_SND)
		;
	
	gLift.mDoor.mConDoorOpen = true;
	gLift.mDoor.mConDoorClose = true;
	
	while (gLift.mDoor.mState != DOOR_CLOSED)
		;
	
	FireKey = false;	
	
	
	
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