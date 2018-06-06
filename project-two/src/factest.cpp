#include <iostream>
#include <array>

using namespace std;

constexpr std::array<uint64_t, 20> fac() {
	std::array<uint64_t, 20> ret{};
	
	for (int i = 1; i < 20; ++i) {
		uint64_t fac = i;
		for (int j = fac - 1; j > 0; --j) {
			fac *= j;
		}
		ret[i] = fac;
	}
	
	return ret;
}


int main() {
	auto arr = fac();
	
	for (auto i : arr) {
		std::cout << i << " " << endl;
	}
}