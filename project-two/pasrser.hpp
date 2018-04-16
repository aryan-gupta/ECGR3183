

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

struct Token {
	OP mOp;
	REG mRi;
	REG mRj;
	union {
		REG mRk;
		short mIm[2]; // 16 bits (I know but this processor cant handle that swaggry of 19 bits)
	};
};

int main(int argc, char* argv[]) {
	if (argc <= 1) exit (-1);
	
	using std::clog;
	using std::endl;
	using std::cout;
	
	auto pdat = parser(argv[1]);
	
	
}
 
std::vector<Token> parser(std::string file) {
	// The instruction file is orgaized by one 
	// opcode and a data attached to it (one int)
	std::vector<Token> ret;
	
	std::ifstream readFile(file.c_str());
	std::string line; // temp store for each command
	
	while(std::getline(readFile,line)) {
		std::stringstream iss(line);
		
		std::string opcode;
		std::string reg1, reg2, reg3;
		std::string numLiteral;
		
		
		std::getline(iss, opcode, ' ');
		std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
		
		Token t;
		
		// convert token string to token for jump table during run
		if        (opcode == "SET") {
			t.mToken = TKN::SET;
		} else if (opcode == "GET") {
			t.mToken = TKN::GET;
		} else if (opcode == "MOVE") {
			t.mToken = TKN::MOVE;
		} else if (opcode == "FADD") {
			t.mToken = TKN::FADD;
		} else if (opcode == "FSUB") {
			t.mToken = TKN::FSUB;
		} else if (opcode == "FNEG") {
			t.mToken = TKN::WAIT;
		} else if (opcode == "FMUL") {
			t.mToken = TKN::WFLR;
		} else if (opcode == "FDIV") {
			t.mToken = TKN::WDOOR;
		} else if (opcode == "FLOOR") {
			t.mToken = TKN::IRON;
		} else if (opcode == "CEIL") {
			t.mToken = TKN::FIRE;
		} else if (opcode == "ROUND") {
			t.mToken = TKN::DOORO;
		} else if (opcode == "FABS") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "FINV") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "MIN") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "MAX") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "POW") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "SIN") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "COS") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "TAN") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "EXP") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "LOG") {
			t.mToken = TKN::DOORC;
		} else if (opcode == "SQRT") {
			t.mToken = TKN::DOORC;
		} else {
			throw 4; // have an actual exception later
		}
		ret.push_back(t);
	}
	
	return ret;
}
