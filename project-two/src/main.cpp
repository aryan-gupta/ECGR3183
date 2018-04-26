
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>

#include "ieee754.hpp"

using reg_t = ieee754;
using regf_t = float;
using RegFile = reg_t[16];

enum class REG {
	R0 = 0b0000,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15
};

REG rtob(std::string reg) {
	std::transform(reg.begin(), reg.end(), reg.begin(), ::toupper);
	
	if (reg == "R0")
		return REG::R0;
	if (reg == "R1")
		return REG::R1;
	if (reg == "R2")
		return REG::R2;
	if (reg == "R3")
		return REG::R3;
	if (reg =="R4")
		return REG::R4;
	if (reg == "R5")
		return REG::R5;
	if (reg == "R6")
		return REG::R6;
	if (reg == "R7")
		return REG::R7;
	if (reg == "R8")
		return REG::R8;
	if (reg == "R9")
		return REG::R9;
	if (reg == "R10")
		return REG::R10;
	if (reg == "R11")
		return REG::R11;
	if (reg == "R12")
		return REG::R12;
	if (reg == "R13")
		return REG::R13;
	if (reg == "R14")
		return REG::R14;
	if (reg == "R15")
		return REG::R15;
}

enum class OP {
	SET = 0b00000,
	GET,
	MOVE,
	FADD,
	FSUB,
	FNEG,
	FMUL,
	FDIV,
	FLOOR,
	CEIL,
	ROUND,
	FABS,
	FINV,
	MIN,
	MAX,
	POW,
	SIN,
	COS,
	TAN,
	EXP,
	LOG,
	SQRT = 0b10101
	
};

struct Decoded_Instruction {
	OP mOp;
	REG mRi;
	REG mRj;
	union {
		REG mRk;
		regf_t mIm; // 16 bits (I know but this processor cant handle that swaggry of 19 bits)
	};
};

struct Writeback_Instruction {
	bool mUse = false;
	REG mWb;
	reg_t mData;
};

// Global Vars
RegFile gRFile;
std::ifstream gInsMem;

// Functions
std::string fetch(); // fetches next instruc
Decoded_Instruction decode(std::string rawins);
Writeback_Instruction execute(Decoded_Instruction decins);
bool writeback(Writeback_Instruction wbins);

int main(int argc, char* argv[]) {
	if (argc <= 1) exit (-1);
	
	using std::clog;
	using std::endl;
	using std::cout;
	
	gInsMem.open(argv[1]);
	
	while (true) {
		// fetch
		std::string insLine = fetch();
		
		if (insLine == "") break; // we can make this better, basically if the feth gets to the
		// end of the instruction memory it will return an null string and then we can just exit out of the loop
		
		// decode
		Decoded_Instruction decIns = decode(insLine);
		// execute
		Writeback_Instruction wbIns = execute(decIns);
		// writeback
		bool done = writeback(wbIns);
	}
}

std::string fetch() {
	std::string raw = ""; // this holds the raw instruction as a string in the
	// form OP Ri Rj Rk or any other format (with imediate values)
	
	while (std::getline(gInsMem,raw)) {
		// std::cout << raw << std::endl;

		if (raw.empty() or raw == "\r") { // skip all empty lines
			continue;
		}
		
		bool found = false;
		for (auto c : raw) {
			if (c == ' ' or c == '\t')
				continue;
			if (c == '-')
				found = true;
			break;
		}
		
		if (!found)	break;
	}

	return raw;
	
}

void setup2reg(std::stringstream& iss, Decoded_Instruction& t) {
	std::string temp;
	
	std::getline(iss, temp, ',');
	t.mRi = rtob(temp);
	std::getline(iss, temp, ' '); // skip that little space after the comma
	
	iss >> temp;
	if (size_t pos = temp.find("--"); pos == std::string::npos)
		t.mRj = rtob(temp);
	else 
		t.mRj = rtob(temp.substr(0, temp.find_first_of("- \t")));
}

void setup3reg(std::stringstream& iss, Decoded_Instruction& t) {
	std::string temp;
	
	std::getline(iss, temp, ',');
	t.mRi = rtob(temp);
	std::getline(iss, temp, ' '); // skip that little space after the comma
	
	std::getline(iss, temp, ',');
	t.mRj = rtob(temp);
	std::getline(iss, temp, ' '); // skip that little space after the comma
	
	//std::getline(iss, temp);
	iss >> temp; // get the last bit
	// std::cout << temp << std::endl;
	/// @todo Check if there are comments
	
	if (size_t pos = temp.find("--"); pos == std::string::npos)
		t.mRk = rtob(temp);
	else 
		t.mRk = rtob(temp.substr(0, temp.find_first_of("- \t")));
}

Decoded_Instruction decode(std::string rawins) {
	std::stringstream iss(rawins); // convert line to ss so its easier to manipulate
	
	std::string opcode;
	std::string temp;
	
	std::getline(iss, opcode, ' ');
	std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
	
	Decoded_Instruction t;
	// do the rest of the line will be decoded depending on what the opcode is
	// so we want to do this if/else if statements
	
	if        (opcode == "SET") {
		t.mOp = OP::SET;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		std::getline(iss, temp, '#'); // skip that little space after the comma
		
		iss >> temp;
		if (size_t pos = temp.find("--"); pos == std::string::npos)
			t.mIm = stof(temp);
		else 
			t.mIm = stof(temp.substr(0, temp.find_first_of("- \t")));		
	} else if (opcode == "GET") {
		t.mOp = OP::GET;
		
		iss >> temp;
		t.mRi = rtob(temp);
	} else if (opcode == "MOVE") {
		t.mOp = OP::MOVE;
		setup2reg(iss, t);
	} else if (opcode == "FADD") {
		t.mOp = OP::FADD;
		setup3reg(iss, t);
	} else if (opcode == "FSUB") {
		t.mOp = OP::FSUB;
		setup3reg(iss, t);
	} else if (opcode == "FNEG") {
		t.mOp = OP::FNEG;
		setup2reg(iss, t);	
	} else if (opcode == "FMUL") {
		t.mOp = OP::FMUL;
		setup3reg(iss, t);
	} else if (opcode == "FDIV") {
		t.mOp = OP::FDIV;
		setup3reg(iss, t);
	} else if (opcode == "FLOOR") {
		t.mOp = OP::FLOOR;
		setup2reg(iss, t);
	} else if (opcode == "CEIL") {
		t.mOp = OP::CEIL;
		setup2reg(iss, t);
	} else if (opcode == "ROUND") {
		t.mOp = OP::ROUND;
		setup2reg(iss, t);
	} else if (opcode == "FABS") {
		t.mOp = OP::FABS;
		setup2reg(iss, t);
	} else if (opcode == "FINV") {
		t.mOp = OP::FINV;
		setup2reg(iss, t);
	} else if (opcode == "MIN") {
		t.mOp = OP::MIN;
		setup3reg(iss, t);
	} else if (opcode == "MAX") {
		t.mOp = OP::MAX;
		setup3reg(iss, t);
	} else if (opcode == "POW") {
		t.mOp = OP::POW;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		std::getline(iss, temp, ' ');
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		std::getline(iss, temp, '#');
		
		iss >> temp;
		if (size_t pos = temp.find("--"); pos == std::string::npos)
			t.mIm = stoi(temp);
		else 
			t.mIm = stoi(temp.substr(0, temp.find_first_of("- \t")));	
	} else if (opcode == "SIN") {
		t.mOp = OP::SIN;
		setup2reg(iss, t);
	} else if (opcode == "COS") {
		t.mOp = OP::COS;
		setup2reg(iss, t);
	} else if (opcode == "TAN") {
		t.mOp = OP::TAN;
		setup2reg(iss, t);
	} else if (opcode == "EXP") {
		t.mOp = OP::EXP;
		setup2reg(iss, t);
	} else if (opcode == "LOG") {
		t.mOp = OP::LOG;
		setup2reg(iss, t);
	} else if (opcode == "SQRT") {
		t.mOp = OP::SQRT;
		setup2reg(iss, t);
	} else {
		throw 4; // have an actual exception later
	}
	
	return t;
}

Writeback_Instruction execute(Decoded_Instruction decIns) {
	Writeback_Instruction r;
	
	switch (decIns.mOp) { // jump table
		case OP::SET: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = decIns.mIm ;
			return r;
		}
		
		case OP::GET: {
			r.mUse = false;
			reg_t num = gRFile[static_cast<size_t>(decIns.mRi)];
			std::cout << reinterpret_cast<float&>(num) << std::endl;
			return r;
		}

		case OP::MOVE: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[static_cast<size_t>(decIns.mRj)];
			return r;
		}
		
		case OP::FADD: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData =  gRFile[static_cast<size_t>(decIns.mRj)] + gRFile[static_cast<size_t>(decIns.mRk)]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FSUB: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[static_cast<size_t>(decIns.mRj)] - gRFile[static_cast<size_t>(decIns.mRk)]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FNEG: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = -gRFile[static_cast<size_t>(decIns.mRj)]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FMUL: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[static_cast<size_t>(decIns.mRj)] * gRFile[static_cast<size_t>(decIns.mRk)]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FDIV: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[static_cast<size_t>(decIns.mRj)] / gRFile[static_cast<size_t>(decIns.mRk)]; /// @todo move this to ALU object
			// std::cout << r.mData << "  " << gRFile[static_cast<size_t>(decIns.mRj)] << "  " << gRFile[static_cast<size_t>(decIns.mRk)] << std::endl;
			return r;
		}
		
		case OP::FLOOR: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = floor(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			return r;
		}
		
		case OP::CEIL: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = ceil(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			return r;
		}
		
		case OP::ROUND: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = round(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			return r;
		}
		
		case OP::FABS: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = abs(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
		
		case OP::FINV: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = inv(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			return r;
		}
		
		case OP::MIN: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = min(gRFile[static_cast<size_t>(decIns.mRj)], gRFile[static_cast<size_t>(decIns.mRk)]);
			return r;
		}
		
		case OP::MAX: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = max(gRFile[static_cast<size_t>(decIns.mRj)], gRFile[static_cast<size_t>(decIns.mRk)]);
			return r;
		}
		
		case OP::POW: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = pow(gRFile[static_cast<size_t>(decIns.mRj)], (short)decIns.mIm);
			
			return r;
		}
		
		case OP::SIN: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = sin(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
		
		case OP::COS: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = cos(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
		
		case OP::TAN: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = tan(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
		
		case OP::EXP: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = exp(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
		
		
		case OP::LOG: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = log(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
		
		
		case OP::SQRT: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = sqrt(gRFile[static_cast<size_t>(decIns.mRj)]); /// @todo move this to ALU object
			
			return r;
		}
	}
}

bool writeback(Writeback_Instruction wbIns) {
	if (!wbIns.mUse) return false;
	
	gRFile[static_cast<size_t>(wbIns.mWb)] = wbIns.mData;
	return true;
}	
