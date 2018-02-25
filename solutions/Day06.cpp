#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>
#include "../include/Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<int> banks {std::istream_iterator<int>{in}, {}};
	std::map<std::vector<int>, int> history;
	int count = 0;
	while (history.emplace(banks, count++).second) {
		auto max = std::max_element(banks.begin(), banks.end());
		int n = std::exchange(*max, 0);
		while (n--) {
			if (++max == banks.end())
				max = banks.begin();
			++*max;
		}
	}
	if (part2)
		std::cout << history.size() - history[banks] << '\n';
	else
		std::cout << history.size() << '\n';
	return 0;
}	
