#pragma once

enum class ControllerState {
	CTR_ASK = 0b00,
	CTR_UP,
	CTR_DOWN,
	CTR_WAIT_LATCH,
	CTR_WAIT_REPLY,
	CTR_WAIT_DCLOSE,
	
	CTR_DC1 = 0b110,
	CTR_DC2
};

struct Controller {
	ControllerState mState;

	void start();
	
};