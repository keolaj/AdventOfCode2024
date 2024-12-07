#include "day2.h"
#include <vector>
#include <iostream>
#include <fstream>

bool test_vec(std::vector<int> vec) {
	bool ascending = vec[0] < vec[1];
	for (int i = 0; i < vec.size() - 1; ++i) {
		int next = vec[i + 1];
		if (ascending) {
			if (vec[i] > next) {
				return false;
			}
		}
		else {
			if (vec[i] < next) {
				return false;
			}
		}
		int diff = abs(vec[i] - next);
		if (diff < 1 || diff > 3) {
			return false;
		}
	}
	return true;
}

void day_main() {

	std::ifstream reports;
	reports.open("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day2\\reports.txt");

	if (!reports.is_open()) {
		std::cout << "couldn't open file!\n";
		return;
	}
	std::vector<std::vector<int>> report_vec;

	int n;
	int report_index = 0;
	while (!reports.eof()) { // read data into report_vec
		report_vec.push_back({});
		while ((reports >> n) && reports.peek() != '\n')  {
			report_vec[report_index].push_back(n);
		}
		report_vec[report_index].push_back(n);
		++report_index;
	}
	report_vec[report_index-1].pop_back();
	
	int safe_count = 0;
	for (std::vector vec : report_vec) {
		if (test_vec(vec)) {
			++safe_count;
		}
		else {
			std::vector<std::vector<int>> tests;
			for (int i = 0; i < vec.size(); ++i) {
				std::vector<int> temp;
				for (int j = 0; j < vec.size(); ++j) {
					if (i == j) {
						continue;
					}
					temp.push_back(vec[j]);
				}
				tests.push_back(temp);
			}
			for (std::vector vec : tests) {
				if (test_vec(vec)) {
					++safe_count;
					break;
				}
			}
		}
	}

	std::cout << safe_count << "\n";
}