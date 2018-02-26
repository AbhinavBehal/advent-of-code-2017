#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <cstdint>
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

	Program(const std::vector<std::string> &instr, int id) 
	: instrs(instr), regs{{'p', id}}, line(0), sendCount(0) {}

	Result run(Program *other = nullptr)
	{
		if (line >= instrs.size())
			return {true, false, 0};
		std::istringstream ss(instrs[line++]);
		std::string ins, lstr, rstr;
		ss >> ins >> lstr >> rstr;
		std::int64_t rval = util::isNumber(rstr) ? std::stoi(rstr) : regs[rstr[0]];
		if (ins == "snd") {
			std::int64_t lval = util::isNumber(lstr) ? std::stoi(lstr) : regs[lstr[0]];
			if (other) {
				other->send(lval);
				++sendCount;
			} else {
				last = lval;
			}
		} else if (ins == "set") {
			regs[lstr[0]] = rval;
		} else if (ins == "add") {
			regs[lstr[0]] += rval;
		} else if (ins == "mul") {
			regs[lstr[0]] *= rval;
		} else if (ins == "mod") {
			regs[lstr[0]] %= rval;
		} else if (ins == "rcv") {
			if (other) {
				if (msgs.empty()) {
					--line;
					return {false, true, 0};
				}
				regs[lstr[0]] = msgs.front();
				msgs.pop();
			} else {
				return {true, false, last};
			}
		} else if (ins == "jgz") {
			std::int64_t lval = util::isNumber(lstr) ? std::stoi(lstr) : regs[lstr[0]];
			if (lval > 0)
				line += rval - 1;
		}
		return {false, false, 0};
	}

	int timesSent() { return sendCount; }
private:
	std::vector<std::string> instrs;
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
#endif