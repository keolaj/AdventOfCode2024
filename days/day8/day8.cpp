#include "day8.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

void processInput(std::vector<std::vector<char>>& map, const char* path) {
	map.clear();
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
}

void process_frequencies(const std::vector<std::vector<char>>& map, std::unordered_map<char, std::vector<std::pair<int, int>>>& frequencies) {
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == '.') continue;
			frequencies[map[i][j]].push_back({ j, i });
		}
	}
}

bool pair_valid(std::pair<int, int> pair, int size) {
	if (pair.first >= 0 && pair.first < size && pair.second >= 0 && pair.second < size) return true;
	else return false;
}

int antinode_count(std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies, int size) {
	std::unordered_set<int> seen_antifreqs;
	int ret = 0;

	for (const auto& [key, value] : frequencies) {
		for (int i = 0; i < value.size(); ++i) {
			int ihash = value[i].second * size + value[i].first;
			if (!seen_antifreqs.contains(ihash)) {
				seen_antifreqs.insert(ihash);
				++ret;
			}
			for (int j = 0; j < value.size(); ++j) {
				int jhash = value[j].second * size + value[j].first;
				if (!seen_antifreqs.contains(jhash)) {
					seen_antifreqs.insert(jhash);
					++ret;
				}
				if (i == j) continue;
				int dx = value[j].first - value[i].first;
				int dy = value[j].second - value[i].second;
				
				int itx_plus = value[j].first + dx;
				int ity_plus = value[j].second + dy;
				while (pair_valid({ itx_plus, ity_plus }, size)) {
					int hash = ity_plus * size + itx_plus;
					if (!seen_antifreqs.contains(hash)) {
						seen_antifreqs.insert(hash);
						++ret;
					}
					itx_plus += dx;
					ity_plus += dy;
				}
				int itx_minus = value[i].first - dx;
				int ity_minus = value[i].second - dy;
				while (pair_valid({ itx_minus, ity_minus }, size)) {
					int hash = ity_minus * size + itx_minus;
					if (!seen_antifreqs.contains(hash)) {
						seen_antifreqs.insert(hash);
						++ret;
					}
					itx_minus -= dx;
					ity_minus -= dy;
				}
			}
		}
	}

	return ret;
}

void day_main() {

	std::vector<std::vector<char>> map;
	processInput(map, "C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day8\\input.txt");

	std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies;
	process_frequencies(map, frequencies);
	
	auto start = std::chrono::high_resolution_clock::now();
	int result = antinode_count(frequencies, map.size());
	auto end = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	printf("RESULT: %d %d microseconds", result, duration);
}