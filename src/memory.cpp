

void Memory::clearMem() {
	mFloors.clear();
}

void Memory::setFloor(FloorNum flr) {
	mFloors.push(flr);
}

FloorNum getFloor(FloorNum current, ElevState dir) {
	return mFloors.top();
	mFloors.pop();
}