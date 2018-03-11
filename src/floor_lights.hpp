#pragma once

#include <atomic>
#include <cstddef>
#include <thread>

class FloorLights {
	std::thread mThread;
	std::atomic_uchar X20;
	
public:
	FloorLights();
	unsigned char getLights();
	
	void start();
	
};