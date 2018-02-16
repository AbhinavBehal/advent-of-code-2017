#ifndef ARGS_H
#define ARGS_H

#include <utility>
#include <fstream>
#include <iostream>
#include <string>

bool checkArgs(int argc, char **argv, std::ifstream &is, bool &part2)
{
	if (argc != 3)
	{
		std::cout << "Usage: <input_file> <part>\n";
		return false;
	}
	std::ifstream temp(argv[1]);
	if (!temp) {
		return false;
	} else {
		is = std::move(temp);
		part2 = std::stoi(argv[2]) == 2;
		return true;
	}
}

#endif