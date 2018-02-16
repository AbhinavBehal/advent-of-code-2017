#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <limits>
#include "Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::unordered_map<std::string, std::int64_t> registers;
	std::int64_t overallMax = 0;
	for (std::string line; std::getline(in, line); ) {
		std::string regA, regB, op, cond;
		int change, comparison;
		std::istringstream ss(line);
		ss >> regA >> op >> change >> regB >> regB >> cond >> comparison;
		std::int64_t &a = registers[regA];
		std::int64_t &b = registers[regB];
		bool execute = false;
		if (cond == ">")
			execute = b > comparison;
		else if (cond == ">=")
			execute = b >= comparison;
		else if (cond == "==")
			execute = b == comparison;
		else if (cond == "!=")
			execute = b != comparison;
		else if (cond == "<=")
			execute = b <= comparison;
		else if (cond == "<")
			execute = b < comparison;
		if (execute) {
			change = op == "inc" ? change : -change;
			a += change;
			if (a > overallMax)
				overallMax = a;
		}
	}
	if (part2) {
		std::cout << overallMax << '\n';
	} else {
		auto max = std::max_element(
			registers.begin(), 
			registers.end(), 
			[](const auto &p1, const auto &p2){ return p1.second < p2.second; }
		)->second;
		std::cout << max << '\n';
	}
	return 0;
}	
