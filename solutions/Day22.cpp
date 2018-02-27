#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "../include/Args.h"
#include "../include/Point.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::unordered_map<Point, char, Point::Hash> grid;
	Point pos{0, 0};
	Point dir{0, 1};
	for (std::string line; std::getline(in, line); ) {
		for (std::size_t x = 0; x < line.size(); ++x) {
			grid[{static_cast<int>(x), pos.y}] = line[x];
		}
		--pos.y;
	}
	pos.y /= 2;
	pos.x = std::abs(pos.y);
	int iter   = part2 ? 10'000'000 : 10'000;
	int bursts = 0;
	while (iter--) {
		auto it = grid.find(pos);
		if (it != grid.end()) {
			switch (it->second) {
			case '.':
				dir.rotL();
				it->second = part2 ? 'W' : '#';
				break;
			case '#':
				dir.rotR();
				it->second = part2 ? 'F' : '.';
				break;
			case 'W':
				it->second = '#';
				break;
			case 'F':
				dir.reverse();
				it->second = '.';
				break;
			}
		} else {
			dir.rotL();
			grid[pos] = part2 ? 'W' : '#';
		}
		if (grid[pos] == '#')
			++bursts;
		pos += dir;
	}
	std::cout << bursts << '\n';
	return 0;
}
