

void Memory::clearMem() {
	mFloors.clear();
}

bool Memory::isEmpty() {
	return mFloors.empty();
}

void Memory::setFloor(FloorNum flr) {
	mFloors.push(flr);
}

FloorNum Memory::getFloor(FloorNum current, ElevState dir) {
	if (mFloors.size() == 0)
		return getDefaultFloor();
	
	auto flr = mFloors.top();
	mFloors.pop();
	return flr;
}


FloorNum Memory::getDefaultFloor() {
	auto hour = gClk.getHour();
	
	if (hour > 8 and hour < 14)
		return F1;
	
	if (hour >= 14 and hour < 18)
		return F2;
	
	return F1;
}