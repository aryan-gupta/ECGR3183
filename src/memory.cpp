
#include <istream>

class Memory {
	std::vector<FloorNum> floors
	
public:
	FloorNum getFloor(FloorNum current, ElevState dir);
	void clearMem();
	void setFloorbit(std::byte state);
	
};