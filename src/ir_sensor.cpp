


void IR_Sensor::start() {
	/// Start the IR Sensor loop
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
			/// if we get a person through the door in that 2sec then we want to mark startOver
			/// to true and start this process over again
		}
		
		if (startOver) continue; // This repeats the loop if a person
		// walks through if not then IR should be done and we send
		
		/// The return of this function will be the signal that tells
		// the Door FSM that IR Sesor is dont
		mState = IR_OFF;
		return; /// We dont need to start over, the IR sensor is done
	}
}