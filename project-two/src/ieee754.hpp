
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
ieee754 operator/ (ieee754 a, ieee754 b);

ieee754 inv   (ieee754 a);
ieee754 abs   (ieee754 a);
ieee754 min   (ieee754 a, ieee754 b);
ieee754 max   (ieee754 a, ieee754 b);
ieee754 pow   (ieee754 a, short b);
ieee754 sin   (ieee754 a);
ieee754 cos   (ieee754 a);
ieee754 tan   (ieee754 a);
ieee754 exp   (ieee754 a);
ieee754 log   (ieee754 a);
ieee754 sqrt  (ieee754 a);
ieee754 round (ieee754 a);
ieee754 ceil  (ieee754 a);
ieee754 floor (ieee754 a);

