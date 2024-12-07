#include "day4.h"
#include <iostream>
#include <fstream>
#include <vector>

void day_main() {
	std::fstream file("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day4\\input.txt");
	if (!file.is_open()) std::cout << "couldn't open file";

	std::vector<std::vector<char>> data{ {} };

	int line = 0;
	char c;
	while (true) {
		file.get(c);
		if (file.eof()) break;
		if (c != '\n') {
			data[line].push_back(c);
		}
		else {
			++line;
			data.push_back({});
		}
	}
	
	int xmas_count = 0;
	//for (int i = 0; i < data.size(); ++i) {
	//	for (int j = 0; j < data[0].size() - 3; ++j) {
	//		if (data[i][j] == 'X' && data[i][j + 1] == 'M' && data[i][j + 2] == 'A' && data[i][j + 3] == 'S') ++xmas_count;
	//		if (data[i][j] == 'S' && data[i][j + 1] == 'A' && data[i][j + 2] == 'M' && data[i][j + 3] == 'X') ++xmas_count;
	//		if (data[j][i] == 'X' && data[j + 1][i] == 'M' && data[j + 2][i] == 'A' && data[j + 3][i] == 'S') ++xmas_count;
	//		if (data[j][i] == 'S' && data[j + 1][i] == 'A' && data[j + 2][i] == 'M' && data[j + 3][i] == 'X') ++xmas_count;
	//	}
	//}
	//for (int i = 0; i < data.size() - 3; ++i) {
	//	for (int j = 0; j < data.size() - 3; ++j) {
	//		if (data[i][j] == 'X' && data[i + 1][j + 1] == 'M' && data[i + 2][j + 2] == 'A' && data[i + 3][j + 3] == 'S') ++xmas_count;
	//		if (data[i][j] == 'S' && data[i + 1][j + 1] == 'A' && data[i + 2][j + 2] == 'M' && data[i + 3][j + 3] == 'X') ++xmas_count;
	//	}
	//}
	//for (int i = data.size() - 1; i >= 3; --i) {
	//	for (int j = 0; j < data.size() - 3; ++j) {
	//		if (data[i][j] == 'X' && data[i - 1][j + 1] == 'M' && data[i - 2][j + 2] == 'A' && data[i - 3][j + 3] == 'S') ++xmas_count;
	//		if (data[i][j] == 'S' && data[i - 1][j + 1] == 'A' && data[i - 2][j + 2] == 'M' && data[i - 3][j + 3] == 'X') ++xmas_count;
	//	}
	//}
	for (int i = 0; i < data.size() - 2; ++i) {
		for (int j = 0; j < data.size() - 2; ++j) {
			if (data[i][j] == 'M' && data[i][j + 2] == 'S' && data[i + 1][j + 1] == 'A' && data[i + 2][j] == 'M' && data[i + 2][j + 2] == 'S') ++xmas_count;
			if (data[i][j] == 'S' && data[i][j + 2] == 'M' && data[i + 1][j + 1] == 'A' && data[i + 2][j] == 'S' && data[i + 2][j + 2] == 'M') ++xmas_count;
			if (data[i][j] == 'M' && data[i][j + 2] == 'M' && data[i + 1][j + 1] == 'A' && data[i + 2][j] == 'S' && data[i + 2][j + 2] == 'S') ++xmas_count;
			if (data[i][j] == 'S' && data[i][j + 2] == 'S' && data[i + 1][j + 1] == 'A' && data[i + 2][j] == 'M' && data[i + 2][j + 2] == 'M') ++xmas_count;
		}
	}
	std::cout << "xmas count: " << xmas_count << '\n';
}