#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "../include/Args.h"

int main(int argc, char **argv)
{
    std::ifstream in;
    bool part2;
    if (!checkArgs(argc, argv, in, part2)) {
        return -1;
    }
    int a, b;
    std::string input;
    std::getline(in, input);
    a = std::stoi(input.substr(input.find_last_of(' ')));
    std::getline(in, input);
    b = std::stoi(input.substr(input.find_last_of(' ')));
    std::minstd_rand0 genA(a);
    std::minstd_rand  genB(b);
    int iter  = part2 ? 5'000'000 : 40'000'000;
    int count = 0;
    while (iter--) {
        a = genA();
        b = genB();
        if (part2) {
            while (a % 4 != 0)
                a = genA();
            while (b % 8 != 0)
                b = genB();
        }
        if ((a & 0xffff) == (b & 0xffff))
            ++count;
    }
    std::cout << count << '\n';
}
