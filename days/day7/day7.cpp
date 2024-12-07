#include "day7.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <set>
#include <chrono>

// 3123869842195
// 223472064194845
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
	for (operation opit = add; opit != end; opit = (operation)(opit + 1)) {
		if (canEqualValue_helper(vec[0], value, vec, 1, opit)) return true;
	}
	return false;
}

int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

bool canEqualValueBw_helper(int64_t in, const std::vector<int64_t>& vec, int position, operation op) {
	int64_t operand = vec[position];
	int64_t current = in;
	switch (op) {
	case add:
		current -= operand;
		if (current < 0) return false;
		break;
	case multiply:
		if (current % operand != 0) return false;
		current /= operand;
		break;
	case concat:
		int count = 0;
		for (int i = operand; i != 0; i /= 10) {
			++count;
		}
		if (in % power(10, count) != operand) {
			return false;
		}
		current /= power(10, count);
		break;
	}
	if (position == 1) {
		if (current == vec[0]) {
			return true;
		}
		else return false;
	}
	for (operation opit = add; opit != end; opit = (operation)(opit + 1)){
		if (canEqualValueBw_helper(current, vec, position - 1, opit)) return true;
	}
	return false;
}
bool canEqualValueBw(int64_t value, const std::vector<int64_t>& vec) {
	for (operation opit = add; opit != end; opit = (operation)(opit + 1)){
		if (canEqualValueBw_helper(value, vec, vec.size() - 1, opit)) return true;
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
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	printf("FORWARD: %lld %lld us\n", result, duration);

	auto newstart = std::chrono::high_resolution_clock::now();

	uint64_t newresult = 0;
	for (const auto& [key, value] : map) {
		if (canEqualValueBw(key, value)) {
			newresult += key;
		}
	}

	auto newend = std::chrono::high_resolution_clock::now();
	auto newduration = std::chrono::duration_cast<std::chrono::nanoseconds>(newend - newstart).count();

	printf("BACKWARDS: %lld %lld us (%lld x faster)\n", newresult, newduration, (duration / newduration));
}