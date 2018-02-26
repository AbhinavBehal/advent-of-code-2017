#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	int steps;
	in >> steps;
	if (part2) {
		const int iter = 50'000'000;
		int pos = 0;
		int ans = 0;
		for (int i = 1; i <= iter; ++i) {
			while (pos + steps + 1 < i) {
				pos += steps + 1;
				++i;
			}
			pos = ((pos + steps) % i) + 1;
			if (pos == 1)
				ans = i;
		}
		std::cout << ans << '\n';
	} else {
		const int iter = 2017;
		std::vector<int> buffer;
		buffer.push_back(0);
		int pos = 0;
		for (int i = 1; i <= iter; ++i) {
			pos = ((pos + steps) % buffer.size()) + 1;
			buffer.insert(buffer.begin() + pos, i);
		}
		std::cout << buffer[(pos + 1) % buffer.size()] << '\n';
	}
	return 0;
}
