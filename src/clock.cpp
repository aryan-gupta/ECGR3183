
#include "main.hpp"

Clock::Clock() {
	reset(0, 0);
}

void Clock::reset() {
	mStart = clk::now();
}

void Clock::reset(bool hour, unsigned val) {
	if (hour) mHour = val;
	else mMinute = val;
}

// https://stackoverflow.com/questions/15957805/
unsigned Clock::getHour() {
	auto elapsed = clk::now() - mStart;
	auto hour = std::chrono::duration_cast<std::chrono::hours>(elapsed).count();
	auto min = std::chrono::duration_cast<std::chrono::minutes>(elapsed).count();
	
	if ((min + mMinute) >= 60)
		++hour;
	
	// std::cout << "..............................TIME: " << (hour + mHour) << std::endl;
	
	return hour + mHour;
}

unsigned Clock::getMin() {
	time_t tt = clk::to_time_t(mStart);
	tm local_tm = *localtime(&tt);
	return local_tm.tm_min;
}