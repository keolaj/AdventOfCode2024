#include "day10.h"
#include "../helpers.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

bool cantTraverse(const std::vector<std::vector<int>>& map, int x, int y) {
	int current = map[y][x];
	if ((y-1 >= 0 && map[y-1][x] != current + 1) && (y+1 < map.size() && map[y + 1][x] != current + 1) && (x-1 >= 0 && map[y][x - 1] != current + 1) && (x + 1 < map.size() && map[y][x + 1] != current + 1)) return true;
	else return false;
}

void find9(const std::vector<std::vector<int>>& map, int x, int y, std::unordered_set<int>& found9s) {
	int current = map[y][x];

	if (current == 9) {
		found9s.insert(y * map.size() + x);
		return;
	}
	if (cantTraverse(map, x, y)) return;

	if (y - 1 >= 0 && map[y - 1][x] == current + 1) find9(map, x, y-1, found9s);
	if (y + 1 < map.size() && map[y + 1][x] == current + 1) find9(map, x, y+1, found9s);
	if (x - 1 >= 0 && map[y][x - 1] == current + 1) find9(map, x - 1, y, found9s);
	if (x + 1 < map.size() && map[y][x + 1] == current + 1) find9(map, x + 1, y, found9s);
}

int count9(const std::vector<std::vector<int>>& map, int x, int y) {
	int ret = 0;
	int current = map[y][x];

	if (current == 9) return 1;
	if (cantTraverse(map, x, y)) return 0;

	if (y - 1 >= 0 && map[y - 1][x] == current + 1) ret += count9(map, x, y-1);
	if (y + 1 < map.size() && map[y + 1][x] == current + 1) ret += count9(map, x, y+1);
	if (x - 1 >= 0 && map[y][x - 1] == current + 1) ret += count9(map, x - 1, y);
	if (x + 1 < map.size() && map[y][x + 1] == current + 1) ret += count9(map, x + 1, y);

	return ret;
}

int traverseTrail(const std::vector<std::vector<int>>& map, int x, int y) {
	std::unordered_set<int> found9s;
	int ret = 0;
	int current = map[y][x];

	if (y - 1 >= 0 && map[y - 1][x] == current + 1) find9(map, x, y-1, found9s);
	if (y + 1 < map.size() && map[y + 1][x] == current + 1) find9(map, x, y+1, found9s);
	if (x - 1 >= 0 && map[y][x - 1] == current + 1) find9(map, x - 1, y, found9s);
	if (x + 1 < map.size() && map[y][x + 1] == current + 1) find9(map, x + 1, y, found9s);
	
	return found9s.size();
}

void day_main() {
	auto map = processInt2d("C:\\Users\\Keola\\dev\\c++\\AdventOfCode2024\\days\\day10\\input.txt");
	int result1 = 0;
	int result2 = 0;
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == 0) {
				result1 += traverseTrail(map, x, y);
				result2 += count9(map, x, y);
			}
		}
	}
	end:
	printf("PART1: %d\n", result1);
	printf("PART2: %d\n", result2);
}