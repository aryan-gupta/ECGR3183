#pragma once

#include <iostream>
#include <queue>

///// NOT THREAD SAFE /////
// actually doesnt need to be, only thing accessing the meory is the
// controller

class Memory {
	std::queue<FloorNum> mFloors;
	
public:
	FloorNum getFloor(FloorNum current, ElevState dir);
	FloorNum getFloor();
	FloorNum getDefaultFloor();
	void clearMem();
	void setFloor(FloorNum flr);
	bool isEmpty();
	
};