#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <array>
#include <numeric>
#include "Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	int iter = part2 ? 64 : 1;
	std::vector<int> lengths;
	if (part2) {
		lengths.insert(lengths.end(), std::istream_iterator<char>{in}, {});
		lengths.insert(lengths.end(), {17, 31, 73, 47, 23});
	} else {
		std::string input;
		in >> input;
		std::istringstream ss(input);
		for (int i; ss >> i; ) {
			lengths.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
	}
	std::array<int, 256> list;
	std::iota(list.begin(), list.end(), 0);
	int pos = 0, skip = 0;
	while (iter--) {
		for (int len : lengths) {
			std::vector<int> slice(len);
			for (int j = 0; j < len; ++j)
				slice[j] = list[(pos + j) % 256];
			std::reverse(slice.begin(), slice.end());
			for (int j = 0; j < len; ++j)
				list[(pos + j) % 256] = slice[j];
			pos += len + skip;
			++skip;
		}
	}
	if (part2) {
		std::ostringstream ss;
		for (int i = 0; i < 16; ++i) {
			int xored = 0;
			for (int j = i * 16; j < (i + 1) * 16; ++j) {
				xored ^= list[j];
			}
			ss << std::setfill('0') << std::setw(2) << std::hex << xored;
		}
		std::cout << ss.str() << '\n';
	} else {
		std::cout << list[0] * list[1] << '\n';
	}
	return 0;
}	
