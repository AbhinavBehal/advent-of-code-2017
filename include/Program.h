#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <cstdint>
#include <iostream>
#include "Util.h"

class Program
{
public:
	struct Result
	{
		bool finished;
		bool deadlock;
		std::int64_t res;
	};

	struct Instruction
	{
		std::string cmd, lstr, rstr;
	};

	Program(const std::vector<Instruction> &instr, int id = 0) 
	: instrs(instr), regs{{'p', id}}, line(0), sendCount(0) {}

	Result run(Program *other = nullptr)
	{
		if (line >= static_cast<int>(instrs.size()))
			return {true, false, 0};
		auto curr = instrs[line++];
		std::int64_t rval = util::isNumber(curr.rstr) ? std::stoi(curr.rstr) : regs[curr.rstr[0]];
		if (curr.cmd == "snd") {
			std::int64_t lval = util::isNumber(curr.lstr) ? std::stoi(curr.lstr) : regs[curr.lstr[0]];
			if (other) {
				other->send(lval);
				++sendCount;
			} else {
				last = lval;
			}
		} else if (curr.cmd == "set") {
			regs[curr.lstr[0]] = rval;
		} else if (curr.cmd == "add") {
			regs[curr.lstr[0]] += rval;
		} else if (curr.cmd == "sub") {
			regs[curr.lstr[0]] -= rval;
		} else if (curr.cmd == "mul") {
			regs[curr.lstr[0]] *= rval;
		} else if (curr.cmd == "mod") {
			regs[curr.lstr[0]] %= rval;
		} else if (curr.cmd == "rcv") {
			if (other) {
				if (msgs.empty()) {
					--line;
					return {false, true, 0};
				}
				regs[curr.lstr[0]] = msgs.front();
				msgs.pop();
			} else {
				return {true, false, last};
			}
		} else if (curr.cmd == "jgz") {
			std::int64_t lval = util::isNumber(curr.lstr) ? std::stoi(curr.lstr) : regs[curr.lstr[0]];
			if (lval > 0)
				line += rval - 1;
		} else if (curr.cmd == "jnz") {
			std::int64_t lval = util::isNumber(curr.lstr) ? std::stoi(curr.lstr) : regs[curr.lstr[0]];
			if (lval != 0)
				line += rval - 1;
		}
		return {false, false, 0};
	}

	int timesSent() { return sendCount; }

	std::string currentCommand() 
	{ 
		return line >= static_cast<int>(instrs.size()) ? "" : instrs[line].cmd;
	}

private:
	std::vector<Instruction> instrs;
	std::unordered_map<char, std::int64_t> regs;
	std::queue<std::int64_t> msgs;
	std::int64_t last;
	int line;
	int sendCount;

	void send(std::int64_t val)
	{
		msgs.push(val);
	}	
};

std::istream &operator>>(std::istream &is, Program::Instruction& instr)
{
	std::string line;
	std::getline(is, line);
	std::istringstream ss(line);
	ss >> instr.cmd >> instr.lstr >> instr.rstr;
	return is;
}

#endif