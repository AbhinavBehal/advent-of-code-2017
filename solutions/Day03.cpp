#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>
#include "../include/Args.h"
#include "../include/Point.h"

int sumNeighbours(const Point &point, std::unordered_map<Point, int, Point::Hash> &grid)
{
	static const Point neighbours[] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
	int sum = 0;
	for (const auto &p : neighbours)
		sum += grid[point + p];
	return sum;
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	int input;
	in >> input;
	if (part2) {
		std::unordered_map<Point, int, Point::Hash> grid;
		grid[{0, 0}] = 1;
		Point pos{1, 0};
		Point dir{1, 0};
		for (;;) {
			int sum = sumNeighbours(pos, grid);
			if (sum > input) {
				std::cout << sum << '\n';
				break;
			}
			grid[pos] = sum;
			if (pos.x == pos.y || (pos.x < 0 && pos.x == -pos.y) || (pos.x > 0 && pos.x == 1 - pos.y))
				dir.rotL();
			pos += dir;
		}
	} else {
		int layer  = std::ceil(std::sqrt(input)) / 2;
		int corner = (2 * layer + 1) * (2 * layer + 1); 
		int diff   = (corner - input) % (2 * layer);
		std::cout << layer + std::abs(diff - layer) << '\n';
	}
}
