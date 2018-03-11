
#include "main.hpp"

Clock::Clock() {
	reset(0, 0);
}

void Clock::reset(unsigned h, unsigned m) {
	mHour = h;
	mMinute = m;
	
	mStart = clk::now();
}

// https://stackoverflow.com/questions/15957805/
unsigned Clock::getHour() {
	time_t tt = clk::to_time_t(mStart);
	tm local_tm = *localtime(&tt);
	return local_tm.tm_hour;
}

unsigned Clock::getMin() {
	time_t tt = clk::to_time_t(mStart);
	tm local_tm = *localtime(&tt);
	return local_tm.tm_min;
}