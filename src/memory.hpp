
#include <istream>

///// NOT THREAD SAFE /////

class Memory {
	std::queue<FloorNum> mFloors
	
public:
	FloorNum getFloor(FloorNum current, ElevState dir);
	void clearMem();
	void setFloor(FloorNum flr);
	
};