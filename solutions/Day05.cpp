#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<int> instr;
	for (int n; in >> n; )
		instr.push_back(n);
	int n = instr.size();
	int index = 0;
	int steps = 0;
	while (index >= 0 && index < n) {
		if (part2 && instr[index] >= 3)
			index += instr[index]--;
		else
			index += instr[index]++;
		++steps;
	}
	std::cout << steps << '\n';
	return 0;
}
