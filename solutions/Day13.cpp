#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include "../include/Args.h"

bool collision(const std::pair<int, int> &p, int delay = 0)
{
	return (p.first + delay) % ((p.second - 1) * 2) == 0;
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<std::pair<int, int>> scanners;
	for (int depth, range; (in >> depth).ignore(1, ':') >> range; )
		scanners.emplace_back(depth, range);
	if (part2) {
		int delay = 0;
		while (std::any_of(scanners.begin(), scanners.end(), [delay](const auto &p) { return collision(p, delay); }))
			++delay;
		std::cout << delay << '\n';
	} else {
		int sev = 0;
		for (const auto &p : scanners) {
			if (collision(p))
				sev += p.first * p.second;
		}
		std::cout << sev << '\n';
	}
	return 0;
}	
