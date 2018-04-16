
using reg_t = uint32_t;
using RegFile = reg_t[16]
// struct RegFile {
	// reg_t R0;
	// reg_t R1;
	// reg_t R2;
	// reg_t R3;
	// reg_t R4;
	// reg_t R5;
	// reg_t R6;
	// reg_t R7;
	// reg_t R8;
	// reg_t R9;
	// reg_t R10;
	// reg_t R11;
	// reg_t R12;
	// reg_t R13;
	// reg_t R14;
	// reg_t R15
// };

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
	R15,
	R16
};

REG rtob(std::string reg) {
	std::transform(reg.begin(), reg.end(), reg.begin(), ::toupper);
	
	if (reg = "R0")
		return REG::R0;
	if (reg = "R1")
		return REG::R1;
	if (reg = "R2")
		return REG::R2;
	if (reg = "R3")
		return REG::R3;
	if (reg = "R4")
		return REG::R4;
	if (reg = "R5")
		return REG::R5;
	if (reg = "R6")
		return REG::R6;
	if (reg = "R7")
		return REG::R7;
	if (reg = "R8")
		return REG::R8;
	if (reg = "R9")
		return REG::R9;
	if (reg = "R10")
		return REG::R10;
	if (reg = "R11")
		return REG::R11;
	if (reg = "R12")
		return REG::R12;
	if (reg = "R13")
		return REG::R13;
	if (reg = "R14")
		return REG::R14;
	if (reg = "R15")
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
		uint16_t mIm; // 16 bits (I know but this processor cant handle that swaggry of 19 bits)
	};
};

struct Writeback_Instruction {
	bool mUse = false;
	REG mWb;
	reg_t mData;
}

// Global Vars
RegFile gRFile;
std::ifstream gInsMem;

// Functions
std::string fetch(); // fetches next instruc
Decoded_Instruction decode(std::string rawins);
Writeback_Instruction execute(Decoded_Instruction decins);
bool writeback(Writeback_Instruction wbins)

int main(int argc, char* argv[]) {
	if (argc <= 1) exit (-1);
	
	using std::clog;
	using std::endl;
	using std::cout;
	
	gInsMem = std::ifstream{ argv[1] };
	
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
	std::string raw; // this holds the raw instruction as a string in the
	// form OP Ri Rj Rk or any other format (with imediate values)
	
	bool cont = std::getline(gInsMem,raw);
	if (!cont) return ""; // if we are at the end of the file
	return raw;
	
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
	
	
	/// @TODO simplefy these to 3 setup 3 registers, setup 2 registers and others?
	if        (opcode == "SET") {
		t.mOp = OP::SET;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mIm = stoi(temp);
	} else if (opcode == "GET") {
		t.mOp = OP::GET;
		
		std::getline(iss, temp, ' ');
		t.mRi = rtob(temp);
		
	} else if (opcode == "MOVE") {
		t.mOp = OP::MOVE;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);
		
	} else if (opcode == "FADD") {
		t.mOp = OP::FADD;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRk = rtob(temp);
	} else if (opcode == "FSUB") {
		t.mOp = OP::FSUB;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRk = rtob(temp);
	} else if (opcode == "FNEG") {
		t.mOp = OP::FNEG;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);		
	} else if (opcode == "FMUL") {
		t.mOp = OP::FMUL;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRk = rtob(temp);
	} else if (opcode == "FDIV") {
		t.mOp = OP::FDIV;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRk = rtob(temp);
	} else if (opcode == "FLOOR") {
		t.mOp = OP::FLOOR;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "CEIL") {
		t.mOp = OP::CEIL;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "ROUND") {
		t.mOp = OP::ROUND;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "FABS") {
		t.mOp = OP::FABS;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "FINV") {
		t.mOp = OP::FINV;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "MIN") {
		t.mOp = OP::MIN;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRk = rtob(temp);
	} else if (opcode == "MAX") {
		t.mOp = OP::MAX;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRk = rtob(temp);
	} else if (opcode == "POW") {
		t.mOp = OP::POW;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ',');
		t.mRj = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mIm = stoi(temp);		
	} else if (opcode == "SIN") {
		t.mOp = OP::SIN;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "COS") {
		t.mOp = OP::COS;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "TAN") {
		t.mOp = OP::TAN;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "EXP") {
		t.mOp = OP::EXP;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "LOG") {
		t.mOp = OP::LOG;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
	} else if (opcode == "SQRT") {
		t.mOp = OP::SQRT;
		
		std::getline(iss, temp, ',');
		t.mRi = rtob(temp);
		
		std::getline(iss, temp, ' ');
		t.mRj = rtob(temp);	
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
			r.mData = static_cast<reg_t>(decIns.mIm);
			return r;
		}
		
		case OP::GET: {
			std::cout << static_cast<int> (gRFile[decIns.mRi]) << std::endl;
			return r;
		}

		case OP::MOVE: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj];
			return r;
		}
		
		case OP::FADD: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj] + gRFile[decIns.mRk]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FSUB: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj] - gRFile[decIns.mRk]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FNEG: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = -gRFile[decIns.mRj]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FMUL: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj] * gRFile[decIns.mRk]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FDIV: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj] / gRFile[decIns.mRk]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FLOOR: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::CEIL: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::ROUND: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::FABS: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = gRFile[decIns.mRj]; /// @todo move this to ALU object
			if (r.mData < 0)
				r.mData = -r.mData;
			
			return r;
		}
		
		case OP::FINV: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::MIN: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj] < gRFile[decIns.mRk] ? gRFile[decIns.mRj] : gRFile[decIns.mRk]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::MAX: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			r.mData = gRFile[decIns.mRj] > gRFile[decIns.mRk] ? gRFile[decIns.mRj] : gRFile[decIns.mRk]; /// @todo move this to ALU object
			return r;
		}
		
		case OP::POW: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = 1; /// @todo move this to ALU object
			
			while (decIns.mIm >= 0) {
				r.mData *= decIns.mRj;
			}
			
			return r;
		}
		
		case OP::SIN: {
			r.mUse = true;
			r.mWb = decIns.mRi;
			
			r.mData = 1; /// @todo move this to ALU object
			
			return r;
		}
	}
}