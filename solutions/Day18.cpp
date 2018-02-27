#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "../include/Args.h"
#include "../include/Program.h"


int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<Program::Instruction> instrs {std::istream_iterator<Program::Instruction>{in}, {}};
	if (part2) {
		Program p0(instrs, 0), p1(instrs, 1);
		for (;;) {
			auto res0 = p0.run(&p1);
			auto res1 = p1.run(&p0);
			if ((res0.deadlock || res0.finished)  && (res1.deadlock || res1.finished))
				break;
		}
		std::cout << p1.timesSent() << '\n';
	} else {
		Program p(instrs, 0);
		for (;;) {
			auto ret = p.run();
			if (ret.finished) {
				std::cout << ret.res << '\n';
				break;
			}
		}
	}
	return 0;
}
