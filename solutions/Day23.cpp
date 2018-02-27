#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "../include/Args.h"
#include "../include/Program.h"
#include "../include/Util.h"

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<Program::Instruction> instrs{std::istream_iterator<Program::Instruction>{in}, {}};
	if (part2) {
		std::int64_t b    = std::stoi(instrs[0].rstr) * std::stoi(instrs[4].rstr) - std::stoi(instrs[5].rstr);
		std::int64_t c    = b - std::stoi(instrs[7].rstr);
		std::int64_t h    = 0;
		std::int64_t incr = std::stoi(instrs[30].rstr);
		for (std::int64_t i = b; i <= c; i -= incr) {
			if (!util::isPrime(i))
				++h;
		}
		std::cout << h << '\n';
	} else {
		Program p(instrs);
		int count = 0;
		for (;;) {
			auto ret = p.run();
			if (p.currentCommand() == "mul")
				++count;
			if (ret.finished) {
				std::cout << count << '\n';
				break;
			}
		}
	}
	return 0;
}
