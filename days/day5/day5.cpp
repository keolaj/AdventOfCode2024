#include "day5.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>

std::pair<int, int> pair_from_string(std::string& s) {
	std::pair<int, int> ret;
	int first_begin = 0;
	int first_end = s.find_first_not_of("1234567890");
	int second_begin = first_end + 1;
	int second_end = s.size();
	std::string first = s.substr(first_begin, first_end);
	std::string second = s.substr(second_begin, second_end);

	ret.first = atoi(first.c_str());
	ret.second = atoi(second.c_str());
	return ret;
}

bool has_rule(int n, std::unordered_set<int>& contains, std::unordered_map<int, std::vector<int>> rules) {
	for (int check : rules[n]) {
		if (contains.contains(check)) return true;
	}
	return false;
}

bool passes_rule(int n, std::unordered_set<int>& contains, std::unordered_set<int>& seen, std::unordered_map<int, std::vector<int>> rules) {
	bool ret = true;
	if (rules.contains(n)) {
		for (int check : rules[n]) {
			if (contains.contains(check)) {
				if (seen.contains(check)) {
					ret = true;
				}
				else {
					ret = false;
					return ret;
				}
			}
			else {
				continue;
			}
		}
		return ret;
	}
	else {
		return true;
	}
}

void repair_update_order(std::vector<int>& out, std::vector<int>& update, std::unordered_set<int>& contains, std::unordered_map<int, std::vector<int>> rules) {
	int orig_size = update.size();
	out.clear();
	std::unordered_set<int> seen;

	// std::vector<int> update_copy{ update };
	
	while (out.size() < orig_size) {
		for (int i = 0; i < update.size(); ++i) {
			int n = update[i];
			if (passes_rule(n, contains, seen, rules)) {
				seen.insert(n);
				out.push_back(n);
				update.erase(update.begin() + i);
				break;
			}
		}
	}
}

void day_main() {
	std::ifstream input;
	input.open("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day5\\input.txt");

	if (!input.is_open()) {
		std::cout << "couldn't open file";
		return;
	}

	std::unordered_map<int, std::vector<int>> rules;

	std::string rule;
	while (true) {
		std::getline(input, rule);
		if (rule == "") break;
		auto rule_pair = pair_from_string(rule);
		rules[rule_pair.second].push_back(rule_pair.first);
	}
	// std::getline(input, rule);

	std::vector<std::vector<int>> updates{ {} };
	std::string update;
	char c;
	int i = 0;
	while (true) {
		c = input.get();
		if (c == ',' || c == '\n' || c == EOF) {
			updates[i].push_back(atoi(update.c_str()));
			update.clear();
			if (c == '\n') {
				updates.push_back({});
				++i;
			}
			if (c == EOF) break;
		}
		else {
			update += c;
		}
	}

	int result = 0;
	std::unordered_set<int> seen;
	std::unordered_set<int> contains;
	for (auto u : updates) {
		bool correct = true;
		for (int n : u) contains.insert(n);
		for (int n : u) {
			seen.insert(n);

			for (int check : rules[n]) {
				if (contains.contains(check)) {
					if (!seen.contains(check)) {
						correct = false;
					}
				}
			}
		}
		if (correct == true) {
			// result += u[(u.size() / 2)];
		}
		else {
			std::vector<int> updated;
			repair_update_order(updated, u, contains, rules);
			result += updated[updated.size() / 2];
		}
		correct = false;
		seen.clear();
		contains.clear();
	}
	std::cout << result;
}