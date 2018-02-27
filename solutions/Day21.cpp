#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "../include/Args.h"

class Grid
{
public:
	struct Hash
	{
		std::size_t operator()(const Grid &grid) const
		{
			std::size_t hash = 0;
			for (const auto &row : grid.grid)
				for (char c : row)
					hash = (hash << 1) | (c == '#');
			return hash;
		}
	};

	Grid() = default;

	Grid(std::vector<std::vector<char>> grid) 
	: grid(grid), N(grid.size()) {}

	Grid(const std::string &str)
	{
		std::vector<char> row;
		for (char c : str) {
			switch (c)
			{
			case '.':
			case '#':
				row.push_back(c);
				break;
			case '/':
				grid.push_back(row);
				row.clear();
				break;
			}
		}
		grid.push_back(row);
		N = grid.size();
	}

	bool operator==(const Grid &other) const 
	{
		return grid == other.grid;
	}

	Grid& rotate()
	{
		transpose();
		flip();
		return *this;
	}

	Grid& transpose()
	{
		for (std::size_t i = 0; i < N; ++i) {
			for (std::size_t j = i; j < N; ++j) {
				std::swap(grid[i][j], grid[j][i]);
			}
		}
		return *this;
	}

	Grid& flip()
	{
		for (std::size_t i = 0; i < N; ++i) {
			for (std::size_t j = 0; j < N / 2; ++j) {
				std::swap(grid[i][j], grid[i][N - j - 1]);
			}
		}
		return *this;
	}

	Grid region(std::size_t size, std::size_t row, std::size_t col)
	{
		std::vector<std::vector<char>> out(size, std::vector<char>(size));
		for (std::size_t i = 0; i < size; ++i) {
			for (std::size_t j = 0; j < size; ++j) {
				out[i][j] = grid[row * size + i][col * size + j];
			}
		}
		return Grid(out);
	}

	void enhance(const std::unordered_map<Grid, Grid, Grid::Hash> &patterns)
	{
		std::size_t width = N % 2 == 0 ? 2 : 3;
		std::size_t nextWidth = width + 1;
		std::size_t size = (N * nextWidth) / width;
		std::vector<std::vector<char>> out(size, std::vector<char>(size));
		for (std::size_t row = 0; row < N / width; ++row) {
			for (std::size_t col = 0; col < N / width; ++col) {
				auto replacement = patterns.at(region(width, row, col));
				for (std::size_t i = 0; i < nextWidth; ++i) {
					for (std::size_t j = 0; j < nextWidth; ++j) {
						out[row * nextWidth + i][col * nextWidth + j] = replacement.grid[i][j];
					}
				}
			}
		}
		*this = Grid(out);
	}

	int count()
	{
		int n = 0;
		for (const auto &row : grid)
			for (char c : row)
				n += (c == '#' ? 1 : 0);
		return n;
	}

private:
	std::vector<std::vector<char>> grid;
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
		Grid in(line.substr(0, ind));
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
	Grid grid({
		{'.', '#', '.'},
		{'.', '.', '#'},
		{'#', '#', '#'}
	});
	int iter = part2 ? 18 : 5;
	while (iter--) {
		grid.enhance(patterns);
	}
	std::cout << grid.count() << '\n';
	return 0;
}
