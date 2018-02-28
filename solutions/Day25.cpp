#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "../include/Args.h"
#include "../include/Util.h"

struct State
{
	struct Action
	{
		int  write;
		char dir;
		char next;
	};
	Action actions[2];

	char operator()(std::unordered_map<int, int> &tape, int &pos) const {
		auto a = actions[tape[pos]];
		tape[pos] = a.write;
		pos += a.dir == 'r' ? 1 : -1;
		return a.next;
	}
};

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::unordered_map<char, State> program;
	auto state = util::read<char>(in, "Begin in state %c.");
	auto iter  = util::read<int> (in, "Perform a diagnostic checksum after %d steps.");
	for (std::string line; std::getline(in, line); ) {
		auto curr = util::read<char>(in, "In state %c:");
		State s;
		for (int i = 0; i < 2; ++i) {
			auto val = util::read<int>(in, "  If the current value is %d:");
			s.actions[val] = {
				util::read<int> (in, "    - Write the value %d."),
				util::read<char>(in, "    - Move one slot to the %c"),
				util::read<char>(in, "    - Continue with state %c.")
			};
		}
		program.emplace(curr, s);
	}
	std::unordered_map<int, int> tape;
	int pos = 0;
	while (iter--) {
		state = program[state](tape, pos);
	}
	std::cout << std::accumulate(
		tape.begin(), 
		tape.end(), 
		0, 
		[](auto acc, const auto &p) { 
			return acc + p.second; 
		}) << '\n';
	return 0;
}
