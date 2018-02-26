#include <iostream>
#include <fstream>
#include <string>
#include <valarray>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include "../include/Args.h"

struct Particle
{
	std::valarray<int> p{0, 0, 0}, v{0, 0, 0}, a{0, 0, 0};
};

int mag(const std::valarray<int> &arr)
{
	return std::abs(arr).sum();
}

std::valarray<int> mag(const Particle &p)
{
	return {mag(p.p), mag(p.v), mag(p.a)};
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if(!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::vector<Particle> particles;
	for (std::string line; std::getline(in, line); ) {
		Particle p;
		std::sscanf(
			line.c_str(),
			"p=<%d,%d,%d>, v=<%d,%d,%d>, a=<%d,%d,%d>",
			&p.p[0], &p.p[1], &p.p[2], 
			&p.v[0], &p.v[1], &p.v[2], 
			&p.a[0], &p.a[1], &p.a[2]
		);
		particles.emplace_back(std::move(p));
	}
	if (part2) {
		// TODO: work out an analytical solution
		std::vector<bool> alive(particles.size(), true);
		int iter = 100;
		while (iter--) {
			auto p1 = particles.begin();
			auto a1 = alive.begin();
			for (; p1 != particles.end() && a1 != alive.end(); ++p1, ++a1) {
				if (!(*a1))
					continue;
				auto p2 = std::next(p1);
				auto a2 = std::next(a1);
				for (; p2 != particles.end() && a2 != alive.end(); ++p2, ++a2) {
					if (*a2 && std::abs(p1->p - p2->p).sum() == 0) {
						// collision
						*a1 = false;
						*a2 = false;
					}
				}
			}
			for (auto &p : particles)
				p.p += (p.v += p.a);
		}
		std::cout << std::count(alive.begin(), alive.end(), true);
	} else {
		auto comp = [](const Particle &p1, const Particle &p2) {
			// compare acceleration -> velocity -> position
			auto mag1 = mag(p1);
			auto mag2 = mag(p2);
			for (int i = mag1.size() - 1; i >= 0; --i) {
				if (mag1[i] < mag2[i]) 
					return true;
				else if (mag1[i] > mag2[i]) 
					return false;
			}
			return false;
		};
		auto min = std::min_element(particles.begin(), particles.end(), comp);
		std::cout << std::distance(particles.begin(), min) << '\n';
	}
	return 0;
}
