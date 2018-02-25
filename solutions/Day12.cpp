#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <regex>
#include <cstdlib>
#include <queue>
#include "../include/Args.h"

std::unordered_set<int> connectedComponents(const std::unordered_map<int, std::vector<int>> &adjList, int vertex)
{
	std::queue<int> queue;
	queue.push(vertex);
	std::unordered_set<int> components;
	std::vector<bool> marked(adjList.size(), false);
	while (queue.size() > 0) {
		if (!marked[vertex]) {
			components.emplace(vertex);
			for (const auto &v : adjList.at(vertex)) {
				components.emplace(v);
				queue.push(v);
			}
			marked[vertex] = true;
		}
		queue.pop();
		vertex = queue.front();
	}
	return components;
}

std::vector<std::unordered_set<int>> components(const std::unordered_map<int, std::vector<int>> &adjList)
{
	std::vector<bool> marked(adjList.size(), false);
	std::vector<std::unordered_set<int>> out;
	std::vector<bool>::iterator it;
	while ((it = std::find(marked.begin(), marked.end(), false)) != marked.end()) {
		int vertex = std::distance(marked.begin(), it);
		auto components = connectedComponents(adjList, vertex);
		for (int v : components)
			marked[v] = true;
		out.emplace_back(std::move(components));
	}
	return out;
}

int main(int argc, char **argv)
{
	std::ifstream in;
	bool part2;
	if (!checkArgs(argc, argv, in, part2)) {
		return -1;
	}
	static const std::regex r{"\\d+", std::regex::optimize};
	std::unordered_map<int, std::vector<int>> adjList;
	for (std::string line; std::getline(in, line); ) {
		auto nums = std::sregex_iterator(line.begin(), line.end(), r);
		int key = std::stoi(nums->str());
		adjList.emplace(key, std::vector<int>());
		while (++nums != std::sregex_iterator()) {
			adjList[key].push_back(std::stoi(nums->str()));
		}
	}
	if (part2)
		std::cout << components(adjList).size() << '\n';
	else
		std::cout << connectedComponents(adjList, 0).size() << '\n';
	return 0;
}	
