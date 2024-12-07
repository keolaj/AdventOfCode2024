#include "./day1.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <unordered_map>

void day_main() {
	std::ifstream puzzle_input("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\input.txt");
	if (!puzzle_input.is_open()) {
		std::cout << "unable to open input file\n";
	}

	int l_temp;
	int r_temp;

	std::vector<int> left;
	std::vector<int> right;

	std::unordered_map<int, int> counter;

	while (puzzle_input >> l_temp >> r_temp) {
		left.push_back(l_temp);
		right.push_back(r_temp);
	}

	sort(left.begin(), left.end(), [](int a, int b) {return a < b; });
	sort(right.begin(), right.end(), [](int a, int b) {return a < b; });

	int sim_score = 0;
	for (int i = 0; i < left.size(); ++i) {
		for (int j = 0; j < right.size(); ++j) {
			if (left[i] == right[j]) {
				counter[left[i]]++;
			}
		}
		sim_score += left[i] * counter[left[i]];
	}
	std::cout << sim_score << "\n";
}