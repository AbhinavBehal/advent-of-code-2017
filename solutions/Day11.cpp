#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include "../include/Args.h"
#include "../include/Point.h"

int hexDist(const Point &p1, const Point &p2)
{
	int dx   = std::abs(p2.x - p1.x);
	int dy   = std::abs(p2.y - p1.y);
	int diff = std::abs(dx - dy);
	return std::max(diff, std::max(dx, dy));
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	const std::unordered_map<std::string, Point> directions {
		{"n",  { 0,  1}},
		{"ne", { 1,  1}},
		{"se", { 1,  0}},
		{"s",  { 0, -1}},
		{"sw", {-1, -1}},
		{"nw", {-1,  0}}
	};
	Point pos {0, 0};
	int maxDist = 0;
	for (std::string dir; std::getline(in, dir, ','); ) {
		pos += directions.at(dir);
		maxDist = std::max(maxDist, hexDist(pos, {0, 0}));
	}
	if (part2)
		std::cout << maxDist << '\n';
	else
		std::cout << hexDist(pos, {0, 0});
	return 0;
}	
