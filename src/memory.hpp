#pragma once

#include <iostream>
#include <queue>
#include <mutex>

///// NOT THREAD SAFE /////
// actually doesnt need to be, only thing accessing the meory is the
// controller and the inputs 
// f*ck it Im using a mutex, to lazy to thing this through

class Memory {
	std::queue<FloorNum> mFloors;
	std::mutex mGuard;
	
public:
	FloorNum getFloor(FloorNum current, ElevState dir);
	FloorNum getFloor();
	FloorNum getDefaultFloor();
	void clearMem();
	void setFloor(FloorNum flr);
	bool isEmpty();
	
};