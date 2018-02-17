#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <sstream>
#include "Args.h"

int calculateWeight(
	std::string name, 
	const std::unordered_map<std::string, int> &nodes, 
	const std::unordered_map<std::string, std::vector<std::string>> &edges
)
{
	int weight = nodes.at(name);
	for (const auto &e : edges.at(name))
		weight += calculateWeight(e, nodes, edges);
	return weight;
}

std::string findRoot(const std::unordered_map<std::string, int> &weights)
{
	return std::max_element(
		weights.begin(),
		weights.end(),
		[&](const auto &p1, const auto &p2) {
			return weights.at(p1.first) < weights.at(p2.first);
		}
	)->first;
}

int mostCommon(const std::vector<int> &v)
{
	std::unordered_map<int, int> freq;
	for (int i : v)
		++freq[i];
	return std::max_element(
		freq.begin(), 
		freq.end(), 
		[](const auto &p1, const auto &p2) { return p1.second < p2.second; }
	)->first;
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	std::unordered_map<std::string, int> nodes;
	std::unordered_map<std::string, int> totalWeights;
	std::unordered_map<std::string, std::vector<std::string>> edges;
	for (std::string line; std::getline(in, line); ) {
		std::string name = line.substr(0, line.find(' '));
		int weight = std::stoi(line.substr(line.find('(') + 1, line.find(')') - 1));
		nodes.emplace(name, weight);
		auto it = line.find("->");
		if (it != std::string::npos) {
			std::string children = line.substr(it + 2);
			children.erase(std::remove(children.begin(), children.end(), ','), children.end());
			std::istringstream ss(children);
			edges.emplace(name, std::vector<std::string>{std::istream_iterator<std::string>{ss}, {}});
		} else {
			edges.emplace(name, std::vector<std::string>());
		}
	}
	for (const auto &kv : nodes)
		totalWeights.emplace(kv.first, calculateWeight(kv.first, nodes, edges));
	std::string currentNode = findRoot(totalWeights);
	if (part2) {
		int prevDiff = 0;
		while (true) {
			std::vector<int> weights;
			const auto &children = edges[currentNode];
			for (const auto &n : children)
				weights.push_back(totalWeights[n]);
			int common = mostCommon(weights);
			if (std::all_of(
				weights.begin(), 
				weights.end(), 
				[common](const auto &w){ return w == common; }
			)) {
				std::cout << nodes[currentNode] - prevDiff << '\n';
				break;
			} else {
				currentNode = *std::find_if(children.begin(), children.end(), [&, common](const auto &n) {
					return totalWeights[n] != common;
				});
				prevDiff = totalWeights[currentNode] - common;
			}
		}
	} else {
		std::cout << currentNode << '\n';
	}
	return 0;
}	
