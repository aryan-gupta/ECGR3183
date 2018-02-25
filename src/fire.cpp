

#include <iostream>

enum class FireState {
	FIRE_ON = 0b0;
	FIRE_OFF;
	
};

class Fire {
	FireState mState;
	
public:
	void turnFireOn();
	void turnFireOff();
	
	FireState getState();
	
};