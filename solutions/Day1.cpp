#include <iostream>
#include <fstream>
#include <string>
#include "Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::string input;
	in >> input;
	input += input[0];
	const size_t n = input.size() - 1;
	const size_t skip = part2 ? n / 2 : 1;
	int checksum = 0;
	for (size_t i = 0; i < n; ++i) {
		if (input[i] == input[(i + skip) % n])
			checksum += input[i] - '0';
	}
	std::cout << checksum << '\n';
}
