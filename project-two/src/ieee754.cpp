
#include <cstdint>
#include <iostream>
#include <bitset>
#include <array>
#include <cmath>
#include "ieee754.hpp"

typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

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
	short radix_res = radix_a + radix_b;
	
	// std::cout << radix_res << std::endl;
	
	uint32_t man_a, man_b;
	man_a = a.man; // expand to 32 bits
	man_a ^= 0x800000; // turn on the 24th bit
	man_b = b.man;
	man_b ^= 0x800000;
	
	bool sign_res = a.sign bitor b.sign; // c++ or
	
	uint64_t man_res = (uint64_t)man_a * (uint64_t)man_b;
	
	// std::cout << man_a << "  " << std::bitset<64> { man_a }.to_string() << std::endl;
	// std::cout << man_b << "  " << std::bitset<64> { man_b }.to_string() << std::endl;
	// std::cout << man_res << "  " << std::bitset<64> { man_res }.to_string() << std::endl;
	
	int shift = 0;
	while (man_res bitand 0xFFFFFFFF'FF000000) { // if any of the bits > 23 is 1, then bit shift right
		man_res >>= 1;
		++shift;
	}
	
	if (shift > 23) radix_res++;
	
	//std::cout << shift << std::endl;
	
	while (!(man_res bitand 0x800000)) { // remove any bits to get the 23rd bit 1
		man_res <<= 1;
		//radix_res--;
	}
	
	ieee754 res;
	res.man = man_res; // this will only extract the first 23 bits
	res.exp = radix_res + 127;
	res.sign = sign_res;
	return res;
}

ieee754 operator/ (ieee754 a, ieee754 b) {
	float div = reinterpret_cast<float&>(a) / reinterpret_cast<float&>(b);
	return reinterpret_cast<ieee754&>(div);
}

ieee754 inv (ieee754 a) {
	float div = 1.0 / reinterpret_cast<float&>(a);
	return reinterpret_cast<ieee754&>(div);
}

ieee754 abs (ieee754 a) {
	a.sign = 0;
	return a;
}

ieee754 min (ieee754 a, ieee754 b) {
	if (a.sign != b.sign)
		return (a.sign == 0)? b : a;
	
	short radix_a = a.exp - 127;
	short radix_b = b.exp - 127;
	
	if (radix_a != radix_b)
		return (radix_a > radix_b)? b : a;
	
	uint32_t man_a, man_b;
	man_a = a.man; // expand to 32 bits
	man_a ^= 0x800000; // turn on the 24th bit
	man_b = b.man;
	man_b ^= 0x800000;

	if (short diff = radix_a - radix_b; diff > 0) {// true if a > b
		man_b >>= diff;
	} else {
		man_a >>= -diff;
	}
	
	return (man_a > man_b)? b : a;
}

ieee754 max (ieee754 a, ieee754 b) {
	if (a.sign != b.sign)
		return (a.sign == 0)? a : b;
	
	short radix_a = a.exp - 127;
	short radix_b = b.exp - 127;
	
	if (radix_a != radix_b)
		return (radix_a > radix_b)? a : b;
	
	uint32_t man_a, man_b;
	man_a = a.man; // expand to 32 bits
	man_a ^= 0x800000; // turn on the 24th bit
	man_b = b.man;
	man_b ^= 0x800000;

	if (short diff = radix_a - radix_b; diff > 0) {// true if a > b
		man_b >>= diff;
	} else {
		man_a >>= -diff;
	}
	
	return (man_a > man_b)? a : b;
}

ieee754 pow (ieee754 a, short b) {
	ieee754 ans;
	ans = 1.0f;
	while (b --> 0)
		ans = ans * a;
	return ans;
}

static constexpr short FAC_LIMIT = 20;
using fac_t = uint64_t;

constexpr std::array<fac_t, FAC_LIMIT> fac() {
	std::array<fac_t, FAC_LIMIT> ret{};
	
	for (int i = 1; i < FAC_LIMIT; ++i) {
		fac_t fac = i;
		for (int j = fac - 1; j > 0; --j) {
			fac *= j;
		}
		ret[i] = fac;
	}
	
	return ret;
}

static constexpr std::array<fac_t, FAC_LIMIT> factorials = fac();

int some_random_func () {
	int ans2 = ans2 - (1.0 / 1.0);
}

ieee754 sin2 (ieee754 a) {
	ieee754 ans = a;
	for (int i = 1; i < FAC_LIMIT;) {
		float fact;
		
		i += 2;
		fact = factorials[i];
		ans = ans - (pow(a, i) / reinterpret_cast<ieee754&>(fact));
		auto temp = pow(a, i);
		// std::cout << reinterpret_cast<float&>(temp) << "  " << float( factorials[i] ) << "  " << reinterpret_cast<float&>(ans) << std::endl;
		
		i += 2;
		fact = factorials[i];
		ans = ans + (pow(a, i) / reinterpret_cast<ieee754&>(fact));
		temp = pow(a, i);
		// std::cout << reinterpret_cast<float&>(temp) << "  " << float( factorials[i] ) << "  " << reinterpret_cast<float&>(ans) << std::endl;
		
	}
	return ans;
}

ieee754 cos (ieee754 a) {
	ieee754 ans;
	ans = 1.0f;
	for (int i = 0; i < FAC_LIMIT;) {
		float fact;
		
		i += 2;
		fact = factorials[i];
		ans = ans - (pow(a, i) / reinterpret_cast<ieee754&>(fact));
		auto temp = pow(a, i);
		// std::cout << reinterpret_cast<float&>(temp) << "  " << float( factorials[i] ) << "  " << reinterpret_cast<float&>(ans) << std::endl;
		
		i += 2;
		fact = factorials[i];
		ans = ans + (pow(a, i) / reinterpret_cast<ieee754&>(fact));
		temp = pow(a, i);
		// std::cout << reinterpret_cast<float&>(temp) << "  " << float( factorials[i] ) << "  " << reinterpret_cast<float&>(ans) << std::endl;
		
	}
	return ans;
}

ieee754 tan (ieee754 a) {
	return cos(a) / sin2(a);
}