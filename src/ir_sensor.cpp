


void IR_Sensor::start() {
	while (true) {
		mState = IR_BUSY;
		if (IRon) continue;
		
		/// THis first section just loops endlesly until the IRon sensor
		/// gives us a 'no one is here signal'
		
		bool startOver = false;
		auto end = clk::steady_clock::now() + 2s;
		while (clk::steady_clock::now() > end) {
			if (IRon) {
				startOver = true;
				break;
			}
			
			/// This here will loop for 2 seconds or until someone walks through the door
			/// if we get a person through the door then start over at the top
			/// If we dont get a person we break out of loop
		}
		
		if (startOver) continue;
		mState = IR_DONE;
		/// We dont need to start over, the IR sensor is done
		break;
	}
	
	signalDoorClose(); // Signal and close door
	mState = IR_OFF;
}