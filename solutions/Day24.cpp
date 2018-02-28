#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include "../include/Args.h"

struct Component
{
	int p1, p2;
	bool used;
	bool fits(int port) const { return p1 == port || p2 == port; }
};

std::istream &operator>>(std::istream &is, Component &c)
{
	(is >> c.p1).ignore(1, '/') >> c.p2;
	c.used = false;
	return is;
}

template <typename Func>
int search(std::vector<Component> &components, Func &&f, int end = 0, int len = 0, int strength = 0)
{
	for (auto &c : components) {
		if (!c.used && c.fits(end)) {
			c.used = true;
			search(components, std::forward<Func>(f), end ^ c.p1 ^ c.p2, len + 1, strength + c.p1 + c.p2);
			c.used = false;
		}
	}
	return f(len, strength);
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<Component> components{std::istream_iterator<Component>{in}, {}};
	if (part2) {
		std::cout << search(
			components, 
			[len = 0, str = 0](int l, int s) mutable {
				if (l > len) {
					len = l;
					str = s;
				} else if (len == l) {
					str = std::max(str, s);
				}
				return str;
			}) << '\n';
	} else {
		std::cout << search(
			components,
			[str = 0](int l, int s) mutable {
				str = std::max(str, s);
				return str;
			}) << '\n';
	}
	return 0;
}
