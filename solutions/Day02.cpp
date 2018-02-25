#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include "../include/Args.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<std::vector<int>> grid;
	for (std::string line; std::getline(in, line); ) {
		std::istringstream ss(line);
		std::vector<int> row;
		int n;
		while (ss >> n)
			row.push_back(n);
		grid.push_back(row);
	}
	int sum = 0;
	if (part2) {
		for (const auto &row : grid) {
			for (size_t i = 0; i < row.size(); ++i) {
				for (size_t j = 0; i != j && j < row.size(); ++j) {
					int a = row[i];
					int b = row[j];
					if (a % b == 0) {
						sum += a / b;
						goto found;
					} else if (b % a == 0) {
						sum += b / a;
						goto found;
					}
				}
			}
			found:;
		}
	} else {
		for (const auto &row : grid) {
			int max = std::numeric_limits<int>::min();
			int min = std::numeric_limits<int>::max();
			for (int n : row) {
				max = std::max(max, n);
				min = std::min(min, n);
			}
			sum += max - min;
		}
	}
	std::cout << sum << '\n';
}
