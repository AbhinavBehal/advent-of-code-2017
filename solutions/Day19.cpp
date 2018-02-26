#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "../include/Args.h"
#include "../include/Point.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<std::string> grid;
	for (std::string line; std::getline(in, line); )
		grid.push_back(line);
	Point pos{static_cast<int>(grid[0].find('|')), 0};
	int steps = 0;
	for (Point dir{0, 1}; grid[pos.y][pos.x] != ' '; pos += dir, ++steps) {
		char c = grid[pos.y][pos.x];
		if (!part2 && std::isalpha(c))
			std::cout << c;
		if (c == '+') {
			dir.rotL();
			Point p = pos + dir;
			if (grid[p.y][p.x] == ' ')
				dir.reverse();
		}
	}
	if (part2)
		std::cout << steps;
	std::cout << '\n';
}
