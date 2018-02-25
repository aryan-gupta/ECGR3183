
#include <iostream>

class FloorLights {
	std::byte X20;
	
public:
	// turn on: bitor
	// turn off: bitand
	void changeLights();
	std::byte getLights();
	
};