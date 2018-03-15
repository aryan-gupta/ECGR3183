

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
// #include <string_view>

#include "main.hpp"

/// Things to work on if we get time
/**
	- Memory barriers (for atomics and synchronization)
	- Graphics (doubt we will have time) (procrastinators unite tmr)
	
**/

std::atomic_bool FireKey; // This global variable starts
// and stops the Fire state
std::atomic_bool IRon; // This global variable turns on 
// when the a person is walking into an elevator
std::atomic_bool Sound; // Output sound after latching

std::atomic_bool gStop; // start the simulation
std::atomic_bool gStart{ false };

Controller gControl; // the controller
Elevator gLift; // Elevator object
Memory gMem;
Clock gClk;
FloorLights gFL;

void output();
void printer();

struct Token;
// std::vector<Token> parser(std::string_view file); // not using c++ 17
std::vector<Token> parser(std::string file); 
void runner(std::vector<Token>& dat);

int main(int argc, char* argv[]) {
	if (argc <= 1) exit (-1);
	
	using std::clog;
	using std::endl;
	using std::cout;
	
	FireKey = false;
	IRon = false;
	Sound = false;
	gStop = false;
	
	std::thread ptr{ printer };
	
	// The main reason I decided to do this in two steps is because disk read
	// is very slow compared to ram reads. I want to first load the entire
	// file into memory and then run that rather than reading directly from
	// the file and executing live. 
	auto pdat = parser(argv[1]);
	runner(pdat);

	while (!gStop)
		;
	
}

void printer() {
	using std::cout;
	using std::endl;
	
	while (!gStart)
		;
	
	for (int i = 0; true; ++i) {
		cout << "At time = " << i << endl;
		output();
		std::this_thread::sleep_for(1s);
	}
}


void output() {
	using std::cout;
	using std::endl;
	
	cout << "Elevator Floor:  " << std::to_string(static_cast<int>(gLift.mFloor)) << endl;
	cout << "Elevator State:  " << pretty(gLift.mState) << endl;
	cout << "IR Sensor State: " << pretty(gLift.mDoor.mIRSen.mState) << endl;
	cout << "Door State:      " << pretty(gLift.mDoor.mState) << endl;
	cout << "Elevator Stop:   " << gLift.mStop << endl;
	cout << "Door Open Sig:   " << gLift.mDoor.mConDoorOpen << endl;
	cout << "Door Close Sig:  " << gLift.mDoor.mConDoorClose << endl;
	cout << "Fire State:      " << FireKey << endl;
	cout << "X20 register:    " << std::to_string(gFL.getLights()) << endl;
	cout << "Sound:           " << Sound << endl;
	
	cout << endl;
	
	
}

// Ya I know I know, not proper, but I'm procrastinating, Im 
// just going to shove this part here
enum class TKN {
	HOUR,
	MIN,
	ERST,
	MEM,
	START,
	WAIT,
	WFLR,
	WDOOR,
	IRON,
	FIRE,
	DOORO,
	DOORC,
};

struct Token {
	TKN mToken;
	int mData;
};

std::vector<Token> parser(std::string file) {
	// The instruction file is orgaized by one 
	// opcode and a data attached to it (one int)
	std::vector<Token> ret;
	
	std::ifstream readFile(file.c_str());
	std::string line; // temp store for each command
	
	while(std::getline(readFile,line)) {
		std::stringstream iss(line);
		
		// split command and data
		std::string tknstr;
		std::string dat;
		std::getline(iss, tknstr, ' ');
		std::getline(iss, dat);
		
		Token t;
		t.mData = stoi(dat); // convert string number
		
		// convert token string to token for jump table during run
		if        (tknstr == "hour") {
			t.mToken = TKN::HOUR;
		} else if (tknstr == "min") {
			t.mToken = TKN::MIN;
		} else if (tknstr == "erst") {
			t.mToken = TKN::ERST;
		} else if (tknstr == "mem") {
			t.mToken = TKN::MEM;
		} else if (tknstr == "start") {
			t.mToken = TKN::START;
		} else if (tknstr == "wait") {
			t.mToken = TKN::WAIT;
		} else if (tknstr == "waitff") {
			t.mToken = TKN::WFLR;
		} else if (tknstr == "waitfd") {
			t.mToken = TKN::WDOOR;
		} else if (tknstr == "iron") {
			t.mToken = TKN::IRON;
		} else if (tknstr == "fire") {
			t.mToken = TKN::FIRE;
		} else if (tknstr == "dooro") {
			t.mToken = TKN::DOORO;
		} else if (tknstr == "doorc") {
			t.mToken = TKN::DOORC;
		}
		ret.push_back(t);
	}
	
	return ret;
}


void runner(std::vector<Token>& dat) {
	// take the parsed tokens and run it
	for (auto& t : dat) {
		switch (t.mToken) { // this is internally impl by a jump table
		
			// For each token and data pair, do what its supposed to
			case TKN::HOUR:
				gClk.reset(true, t.mData);
			break;
			
			case TKN::MIN:
				gClk.reset(false, t.mData);
			break;
			
			case TKN::ERST:
				gLift.reset(static_cast<FloorNum>(t.mData));
			break;
			
			case TKN::MEM:
				gMem.setFloor(static_cast<FloorNum>(t.mData));
			break;
			
			case TKN::START:
				gClk.reset();
				gStart = true;
			break;
			
			case TKN::WAIT:
				std::this_thread::sleep_for(std::chrono::seconds{ t.mData });
			break;
			
			case TKN::WFLR:
				while (gLift.mFloor != static_cast<FloorNum>(t.mData));
			break;
			
			case TKN::WDOOR:
				while (gLift.mDoor.mState != static_cast<DoorState>(t.mData));
			break;
			
			case TKN::IRON:
				IRon = static_cast<bool>(t.mData);
			break;
			
			case TKN::FIRE:
				FireKey = static_cast<bool>(t.mData);
			break;
			
			case TKN::DOORO:
				gLift.mDoor.mConDoorOpen = true;
			break;
			
			case TKN::DOORC:
				gLift.mDoor.mConDoorClose = true;
			break;
		}
	}
}