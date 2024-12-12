#include <vector>
#include <iostream>
#include <fstream>

std::vector<char> processChar(const char* path) {
	std::vector<char> map;
	std::ifstream input{ path };
	if (!input.is_open()) {
		std::cout << "couldn't open file\n";
		return map;
	}
	char c;
	while (true) {
		input.get(c);
		if (input.eof()) break;
		map.push_back(c);
	}
	return map;
}

std::vector<std::vector<char>> processChar2d(const char* path) {
	std::vector<std::vector<char>> map;
	std::ifstream input{ path };
	if (!input.is_open()) {
		std::cout << "couldn't open file\n";
		return map;
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

std::vector<uint64_t> processInt(const char* path) {
	std::vector<uint64_t> map;
	std::ifstream input{ path };
	if (!input.is_open()) {
		std::cout << "couldn't open file\n";
		return map;
	}
	uint64_t n;
	while (true) {
		input >> n;
		map.push_back(n);
		if (input.eof()) break;
	}
	return map;
}

std::vector<std::vector<int>> processInt2d(const char* path) {
	std::vector<std::vector<int>> map;
	std::ifstream input{ path };
	if (!input.is_open()) {
		std::cout << "couldn't open file\n";
		return map;
	}
	char c;
	int line = 0;
	map.push_back({});
	while (true) {
		input.get(c);
		if (input.eof()) break;
		if (c != '\n') {
			if (c == '.') {
				map[line].push_back(INT_MAX);
				continue;
			}
			map[line].push_back(c - '0');
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

