#pragma once

#include <chrono>

#include "main.hpp"

class Clock {
	typename clk::time_point mStart; // this stores when the simulation
	// started, it is absolute
	
	unsigned mHour; // this stores the start time, it wont change
	// unless the simulation changes.
	unsigned mMinute;
	
	// Forexample if the simulation states that it started at 14:59 then the 
	// mAbsTime will store the start of the system clock, and mHour will store
	// 14 and mMinute stores 59. To figure out the current time 
	
public:
	Clock();
	
	void reset(unsigned h, unsigned m);
	
	unsigned getHour();
	unsigned getMin();
};