#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::vector<char>> processChar2d(const char* path) {
	std::vector<std::vector<char>> map;
	std::ifstream input{ path };
	if (!input.is_open()) {
		std::cout << "couldn't open file\n";
		return;
	}
	char c;
	int line = 0;
	map.push_back({});
	while (true) {
		input.get(c);
		if (input.eof()) break;
		if (c != '\n') {
			map[line].push_back(c);
		}
		else {
			++line;
			map.push_back({});
		}
	}
	return map;
}

template <typename T>
void print2d(std::vector<std::vector<T>> map) {
	for (auto v : map) {
		for (auto e : v) {
			std::cout << e << ' ';
		}
		std::cout << '\n';
	}
}

