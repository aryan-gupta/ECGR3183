
#include <iostream>

class FloorLights {
	std::thread mThread;
	std::atomic_uchar X20;
	
	void operator() ();
	
public:
	FloorLights();
	std::byte getLights();
	
};