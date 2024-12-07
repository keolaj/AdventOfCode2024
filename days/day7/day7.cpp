#include "day7.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <set>
#include <chrono>

enum operation {
	add,
	multiply,
	concat,
	end
};

std::string filterString(const std::string s, const std::function<bool (char)>& filter) {
	std::string ret;
	for (char c : s) {
		if (filter(c)) ret += c;
	}
	return ret;
}

void populateMapFromString(const std::string& s, std::unordered_map<int64_t, std::vector<int64_t>>& map) {
	auto fs = filterString(s, [](char c) {return c != ':'; });
	std::stringstream ss(fs);
	int64_t key;
	ss >> key;
	int64_t value;
	while (ss >> value) {
		map[key].push_back(value);
	}
}

bool canEqualValue_helper(int64_t current_val, int64_t wanted_val, const std::vector<int64_t>& vec, int64_t position, operation op) {
	if (position == vec.size()) return current_val == wanted_val;
	
	int64_t next_val = current_val;
	switch (op) {
	case add:
		next_val += vec[position];
		break;
	case multiply:
		next_val *= vec[position];
		break;
	case concat:
		for (int x = vec[position]; x != 0; x /= 10) {
			next_val *= 10;
		}
		next_val += vec[position];
		break;
	}
	if (next_val > wanted_val) return false;
	for (operation opit = add; opit != end; opit = (operation)(opit + 1)) {
		if (canEqualValue_helper(next_val, wanted_val, vec, position + 1, opit)) return true;
	}
	return false;
}

bool canEqualValue(int64_t value, const std::vector<int64_t>& vec) {
	bool rets[end]{};
	for (operation opit = add; opit != end; opit = (operation)(opit + 1)) {
		if (canEqualValue_helper(vec[0], value, vec, 1, opit)) return true;
	}
	return false;
}

void day_main() {
	std::ifstream input("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day7\\input.txt");

	if (!input.is_open()) {
		printf("couldn't open file");
	}
	
	std::unordered_map<int64_t, std::vector<int64_t>> map;
	
	std::string s;
	while (std::getline(input, s)) populateMapFromString(s, map);

	auto start = std::chrono::high_resolution_clock::now();

	uint64_t result = 0;
	for (const auto& [key, value] : map) {
		if (canEqualValue(key, value)) {
			result += key;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	printf("RESULT: %lld %lld ms", result, duration.count());

}