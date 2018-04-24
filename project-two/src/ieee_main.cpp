
#include <iostream>
#include <bitset>

#include "ieee754.hpp"
using namespace std;

int main() {
	ieee754 num1, num2;
	
	// num1 = 3.14159f;
	num1 = 5.0f;
	// std::bitset<32> in1 { cast<uint32_t>(num1) };
	// cout << in1.to_string() << endl;
	
	num2 = 5.0;
	
	// cout << cast<float>(num1) << endl;
	// cout << cast<float>(num2) << endl;
	
	// auto addf = sin(5.0f);
	
	//auto add = pow(num1, 7);
	auto add = log(num1);
	//auto add = inverse(num1);
	//auto add = num1 * num2;
	
	cout << reinterpret_cast<float&>(add) << endl;
	
	// std::bitset<32> out { reinterpret_cast<uint32_t&>(add) }; // I think I just caused
	// // major UB here but im just testing lol
	// cout << out.to_string() << endl;
}