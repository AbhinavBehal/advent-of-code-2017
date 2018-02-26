#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include "../include/Args.h"

class Move
{
public:
	virtual ~Move() {}
	virtual void run(std::string &programs) = 0;
};

class Spin : public Move
{
public:
	Spin(int n) : n(n) {}

	virtual void run(std::string &programs)
	{
		std::rotate(programs.rbegin(), programs.rbegin() + n, programs.rend());
	}
private:
	int n;
};

class Exchange : public Move
{
public:
	Exchange(int p1, int p2) : p1(p1), p2(p2) {}

	virtual void run(std::string &programs)
	{
		std::swap(programs[p1], programs[p2]);
	}
private:
	int p1;
	int p2;
};

class Partner : public Move
{
public:
	Partner(char a, char b) : a(a), b(b) {}

	virtual void run(std::string &programs)
	{
		auto p1 = programs.find(a);
		auto p2 = programs.find(b);
		std::swap(programs[p1], programs[p2]);
	}
private:
	char a;
	char b;
};

int main(int argc, char **argv)
{
    std::ifstream in;
    bool part2;
    if (!checkArgs(argc, argv, in, part2)) {
        return -1;
    }
	const int iter = part2 ? 1'000'000'000 : 1;
	std::string programs = "abcdefghijklmnop";
	std::vector<std::unique_ptr<Move>> moves;
	std::unordered_map<std::string, int> memory;
	for (std::string line; std::getline(in, line, ','); ) {
		std::istringstream ss(line);
		char move, slash;
		ss >> move;
		switch (move) {
		case 's':
			int n;
			ss >> n;
			moves.emplace_back(new Spin(n));
			continue;
		case 'x':
			int p1, p2;
			ss >> p1 >> slash >> p2;
			moves.emplace_back(new Exchange(p1, p2));
			continue;
		case 'p':
			char programA, programB;
			ss >> programA >> slash >> programB;
			moves.emplace_back(new Partner(programA, programB));
			continue;
		}
	}
	for (int i = 0; i < iter; ++i) {
		if (part2 && memory.count(programs)) {
			// found the cycle
			int pos = iter % i;
			programs = std::find_if(
				memory.begin(), 
				memory.end(), 
				[pos](const auto &p){ return p.second == pos; }
			)->first;
			break;
		}
		memory.emplace(programs, i);
		for (const auto &m : moves)
			m->run(programs);
	}
	std::cout << programs << '\n';
}
