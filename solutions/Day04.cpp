#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include "../include/Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	int count = 0;
	for (std::string line; std::getline(in, line); ) {
		std::unordered_set<std::string> passwords;
		std::istringstream ss(line);
		bool valid = true;
		for (std::string password; ss >> password; ) {
			if (part2)
				std::sort(password.begin(), password.end());
			if (!passwords.insert(password).second) {
				valid = false;
				break;
			}
		}
		if (valid)
			++count;
	}
	std::cout << count << '\n';
	return 0;
}
