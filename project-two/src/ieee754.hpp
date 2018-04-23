
/// The only reason Im doing it this way is for type-saftey and for
// the addition of realism
struct ieee754 {
	unsigned  man  : 23;
	unsigned  exp  : 8;
	unsigned  sign : 1;
	
	ieee754 operator= (float b);
};

// Im defining this outside the class cause of realism
ieee754 operator- (ieee754 a);
ieee754 operator+ (ieee754 a, ieee754 b);
ieee754 operator- (ieee754 a, ieee754 b);
ieee754 operator* (ieee754 a, ieee754 b);