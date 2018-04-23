
#include <cstdint>
#include <iostream>
#include <bitset>
#include "ieee754.hpp"

ieee754 ieee754::operator= (float b) {
	*this = reinterpret_cast<ieee754&>(b);
	return *this;
}

ieee754 operator- (ieee754 a) {
	a.sign = !a.sign;
	return a;	
}

ieee754 operator+ (ieee754 a, ieee754 b) {
	short radix_a = a.exp - 127;
	short radix_b = b.exp - 127;
	short radix_sum = 0;
	
	uint32_t man_a, man_b;
	man_a = a.man; // expand to 32 bits
	man_a ^= 0x800000; // turn on the 24th bit
	man_b = b.man;
	man_b ^= 0x800000;
	
	//std::cout << std::bitset<32> { man_a }.to_string() << std::endl;
	//std::cout << std::bitset<32> { man_b }.to_string() << std::endl;
	
	bool sign_sum = 0;
	
	if (short diff = radix_a - radix_b; diff > 0) {// true if a > b
		man_b >>= diff;
		radix_sum = radix_a;
	} else {
		man_a >>= -diff;
		radix_sum = radix_b;
	}
	
	uint32_t man_sum{};
	
	if (a.sign == b.sign) { // c++ xnor
		man_sum = man_b + man_a;
		sign_sum = a.sign;
	} else if (a.sign) { // a is negative
		if        (man_a > man_b) {
			man_sum = man_a - man_b;
			sign_sum = 1;
		} else if (man_a < man_b) {
			man_sum = man_b - man_a;
			sign_sum = 0;
		} else {
			// zero
		}
	} else { // b is negative
		if        (man_b > man_a) {
			man_sum = man_b - man_a;
			sign_sum = 1;
		} else if (man_b < man_a) {
			man_sum = man_a - man_b;
			sign_sum = 0;
		} else {
			// zero
		}
	}
	
	//std::cout << std::bitset<32> { man_sum }.to_string() << std::endl;
	
	while (man_sum bitand 0xFF000000) { // if any of the bits > 23 is 1, then bit shift right
		man_sum >>= 1;
		radix_sum++;
	}
	
	while (!(man_sum bitand 0x800000)) { // remove any bits to get the 23rd bit 1
		man_sum <<= 1;
		radix_sum--;
	}
	
	ieee754 sum;
	sum.man = man_sum; // this will only extract the first 23 bits
	sum.exp = radix_sum + 127;
	sum.sign = sign_sum;
	return sum;
}

ieee754 operator- (ieee754 a, ieee754 b) {
	return operator+ (a, -b);
}

ieee754 operator* (ieee754 a, ieee754 b) {
	short radix_a = a.exp - 127;
	short radix_b = b.exp - 127;
	short radix_res = radix_a * radix_b;
	
	uint32_t man_a, man_b;
	man_a = a.man; // expand to 32 bits
	man_a ^= 0x800000; // turn on the 24th bit
	man_b = b.man;
	man_b ^= 0x800000;
	
	bool sign_res = a.sign ^ b.sign; // c++ or
	
	uint32_t man_res = man_a * man_b;
	
	while (man_res bitand 0xFF000000) { // if any of the bits > 23 is 1, then bit shift right
		man_res >>= 1;
		man_res++;
	}
	
	while (!(man_res bitand 0x800000)) { // remove any bits to get the 23rd bit 1
		man_res <<= 1;
		man_res--;
	}
	
	ieee754 res;
	res.man = man_res; // this will only extract the first 23 bits
	res.exp = radix_res + 127;
	res.sign = sign_res;
	return res;
}