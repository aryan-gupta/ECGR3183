

struct Fetch {
	std::ifstream mFile;
	
	
	Fetch();
	
	std::string operator() ();
	
};