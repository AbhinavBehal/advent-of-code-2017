#include <iostream>
#include <string>
#include <fstream>
#include "../include/Args.h"

enum class State
{
	Normal, Garbage, Ignore
};

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	int depth = 0, score = 0, garbage = 0;
	State state = State::Normal;
	for (char c; in >> c; ) {
		switch (state) {
		case State::Normal:
			switch (c) {
			case '{': 
				++depth;
				continue;
			case '}': 
				score += depth--;
				continue;
			case '<': 
				state = State::Garbage; 
				continue;
			default:
				continue;
			}
		case State::Garbage:
			switch (c) {
			case '>': 
				state = State::Normal;
				continue;
			case '!': 
				state = State::Ignore;
				continue;
			default: 
				++garbage;
				continue;
			}
			continue;
		case State::Ignore:
			state = State::Garbage;
			continue;
		}
	}
	std::cout << (part2 ? garbage : score) << '\n';
	return 0;
}	
