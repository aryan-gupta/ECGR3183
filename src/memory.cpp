
#include <mutex>

#include "main.hpp"

// deprecated cant use [[depreciated]]
void Memory::clearMem() {
	std::lock_guard<std::mutex> { mGuard };
	
	// https://stackoverflow.com/questions/709146
	decltype(mFloors) empty; // swap with an empty one
	std::swap(mFloors, empty);
}

bool Memory::isEmpty() {
	return mFloors.empty();
}

void Memory::setFloor(FloorNum flr) {
	if (FireKey) {
		mFireFloor = flr;
		return;
	}
	
	std::lock_guard<std::mutex> { mGuard }; // Protection
	mFloors.push(flr);
}

FloorNum Memory::getFloor() {
	if (FireKey) // no need for protection 
		return mFireFloor;
	
	std::lock_guard<std::mutex> { mGuard };
	
	if (mFloors.empty())
		return getDefaultFloor();
	
	auto flr = mFloors.front();
	mFloors.pop();
	return flr;
}


FloorNum Memory::getDefaultFloor() {
	// return F1; /// FOR TESTING PURPOSES ONLY
	auto hour = gClk.getHour();
	
	// std::cout << "........................................" << std::to_string(hour) << std::endl;
	
	if (hour > 8 and hour < 14)
		return F1;
	
	if (hour >= 14 and hour < 18)
		return F2;
	
	return F1;
}