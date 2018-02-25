#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_set>
#include "../include/Args.h"
#include "../include/Util.h"
#include "../include/Point.h"

std::string hexToBin(const std::string &str)
{
	std::string out;
	for (char c : str) {
		switch (std::toupper(c)) {
		case '0': out += "0000"; continue;
		case '1': out += "0001"; continue;
		case '2': out += "0010"; continue;
		case '3': out += "0011"; continue;
		case '4': out += "0100"; continue;
		case '5': out += "0101"; continue;
		case '6': out += "0110"; continue;
		case '7': out += "0111"; continue;
		case '8': out += "1000"; continue;
		case '9': out += "1001"; continue;
		case 'A': out += "1010"; continue;
		case 'B': out += "1011"; continue;
		case 'C': out += "1100"; continue;
		case 'D': out += "1101"; continue;
		case 'E': out += "1110"; continue;
		case 'F': out += "1111"; continue;
		}
	}
	return out;
}

std::unordered_set<Point, Point::Hash> neighbours(const std::array<std::array<char, 128>, 128> &grid, int x, int y)
{
	std::vector<Point> stack;
	stack.push_back({x, y});
	std::unordered_set<Point, Point::Hash> component;
	while (stack.size() > 0) {
		auto v = stack.back();
		stack.pop_back();
		if (component.find(v) == component.end()) {
			component.insert(v);
			if (v.x > 0 && grid[v.y][v.x - 1] == '1')    // left
				stack.push_back({v.x - 1, v.y});
			if (v.x < 127 && grid[v.y][v.x + 1] == '1')  // right
				stack.push_back({v.x + 1, v.y});
			if (v.y > 0 && grid[v.y - 1][v.x] == '1')    // above
				stack.push_back({v.x, v.y - 1});
			if (v.y < 127 && grid[v.y + 1][v.x] == '1')  // below
				stack.push_back({v.x, v.y + 1});
		}
	}
	return component;
}

int regions(const std::array<std::array<char, 128>, 128> &grid)
{
	std::unordered_set<Point, Point::Hash> marked;
	int count = 0;
	for (int y = 0; y < 128; ++y) {
		for (int x = 0; x < 128; ++x) {
			if (grid[y][x] == '1' && marked.find({x, y}) == marked.end()) {
				auto comp = neighbours(grid, x, y);
				for (const auto &p : comp)
					marked.insert(p);
				++count;
			}
		}
	}
	return count;
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::string input;
	in >> input;
	std::array<std::array<char, 128>, 128> grid;
	for (int i = 0; i < 128; ++i) {
		auto str = hexToBin(util::knotHash(input + '-' + std::to_string(i)));
		for (int j = 0; j < 128; ++j)
			grid[i][j] = str[j];
	}
	if (part2) {
		std::cout << regions(grid) << '\n';
	} else {
		int count = 0;
		for (const auto &row : grid) {
			for (char c : row) {
				if (c == '1')
					++count;
			}
		}
		std::cout << count << '\n';
	}
	return 0;
}
