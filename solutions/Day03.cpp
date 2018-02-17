#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>
#include "Args.h"

struct Point
{
	int x;
	int y;
	void rotL()
	{
		x = -std::exchange(y, x);
	}
	int dist(const Point &p) const
	{
		return std::abs(x - p.x) + std::abs(y - p.y);
	}
	Point &operator+=(const Point &p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}
	Point operator+(const Point &p) const
	{
		return Point(*this) += p;
	}
	bool operator==(const Point &p) const 
	{
		return x == p.x && y == p.y;
	}
	struct Hash
	{
		std::size_t operator()(const Point &p) const 
		{
			return (p.y << 16) ^ p.x;
		}
	};
};

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
		int corner = std::pow((2 * layer + 1), 2); 
		int diff   = (corner - input) % (2 * layer);
		std::cout << layer + std::abs(diff - layer) << '\n';
	}
}
