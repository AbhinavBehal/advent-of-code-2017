#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <initializer_list>
#include <cmath>
#include "../include/Args.h"

class Grid
{
public:
	struct Hash
	{
		std::size_t operator()(const Grid &grid) const
		{
			std::size_t hash = 0;
			for (char c : grid.data)
					hash = (hash << 1) | (c == '#');
			return hash;
		}
	};

	Grid() = default;

	Grid (std::size_t size)
	: data(size * size), N(size) {}

	Grid(std::initializer_list<char> list) 
	: data(list), N(std::sqrt(list.size())) {}

	Grid(const std::string &str)
	{
		for (char c : str) {
			if (c == '/') 
				continue;
			data.push_back(c);
		}
		N = std::sqrt(data.size());
	}

	char &at(std::size_t r, std::size_t c)
	{
		return data[r * N + c];
	}

	bool operator==(const Grid &other) const 
	{
		return data == other.data;
	}

	Grid& rotate()
	{
		transpose();
		flip();
		return *this;
	}

	Grid& transpose()
	{
		for (std::size_t r = 0; r < N; ++r) {
			for (std::size_t c = r; c < N; ++c) {
				std::swap(at(r, c), at(c, r));
			}
		}
		return *this;
	}

	Grid& flip()
	{
		for (std::size_t r = 0; r < N; ++r) {
			for (std::size_t c = 0; c < N / 2; ++c) {
				std::swap(at(r, c), at(r, N - c - 1));
			}
		}
		return *this;
	}

	Grid region(std::size_t size, std::size_t row, std::size_t col)
	{
		Grid out(size);
		for (std::size_t r = 0; r < size; ++r) {
			for (std::size_t c = 0; c < size; ++c) {
				out.at(r, c) = at(row * size + r, col * size + c);
			}
		}
		return out;
	}

	void enhance(const std::unordered_map<Grid, Grid, Grid::Hash> &patterns)
	{
		std::size_t width = N % 2 == 0 ? 2 : 3;
		std::size_t nextWidth = width + 1;
		std::size_t size = (N * nextWidth) / width;
		Grid out(size);
		for (std::size_t row = 0; row < N / width; ++row) {
			for (std::size_t col = 0; col < N / width; ++col) {
				auto replacement = patterns.at(region(width, row, col));
				for (std::size_t i = 0; i < nextWidth; ++i) {
					for (std::size_t j = 0; j < nextWidth; ++j) {
						out.at(row * nextWidth + i, col * nextWidth + j) = replacement.at(i, j);
					}
				}
			}
		}
		*this = out;
	}

	int count()
	{
		return std::count(data.begin(), data.end(), '#');
	}
private:
	std::vector<char> data;
	std::size_t N;
};

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::unordered_map<Grid, Grid, Grid::Hash> patterns;
	for (std::string line; std::getline(in, line); ) {
		auto ind = line.find("=>");
		Grid in(line.substr(0, ind - 1));
		Grid out(line.substr(ind + 3));
		// setup all rotations of the input pattern
		patterns[in] = out;
		patterns[in.rotate()] = out;
		patterns[in.rotate()] = out;
		patterns[in.rotate()] = out;
		patterns[in.rotate().flip()] = out;
		patterns[in.rotate()] = out;
		patterns[in.rotate()] = out;
		patterns[in.rotate()] = out;
	}
	Grid grid{'.', '#', '.', '.', '.', '#', '#', '#', '#'};
	int iter = part2 ? 18 : 5;
	while (iter--) {
		grid.enhance(patterns);
	}
	std::cout << grid.count() << '\n';
	return 0;
}
