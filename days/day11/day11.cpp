#include "day11.h"
#include "../helpers.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <forward_list>

uint64_t exp(uint64_t base, uint64_t exponent) {
	if (exponent == 0) {
		return 1;
	}
	else if (exponent < 0) {
		return 1 / exp(base, -exponent);
	}
	else {
		return base * exp(base, exponent - 1);
	}
}

std::pair<uint64_t, uint64_t> transformStone(uint64_t stone, std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>>& transformations) {
	if (transformations.contains(stone)) {
		return transformations[stone];
	}
	if (stone == 0) {
		transformations[stone] = { 1, UINT64_MAX };
		return { 1, UINT64_MAX };
	}
	else {
		uint64_t power = 0;
		for (uint64_t i = stone; i != 0; i /= 10) {
			++power;
		}
		if (power % 2 == 0) {
			uint64_t higher = stone / (exp(10, power / 2));
			uint64_t lower = stone - (higher * (exp(10, power / 2)));

			transformations[stone] = { higher, lower };
			return { higher, lower };
		}
		else {
			transformations[stone] = { stone * 2024, UINT64_MAX };
			return { stone * 2024, UINT64_MAX };
		}
	}

}

void blink(std::forward_list<uint64_t>& stones, std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>>& transformations) {
	for (auto it = stones.begin(); it != stones.end(); ++it) {
		auto stone = *it;
		auto newStones = transformStone(stone, transformations);
		*it = newStones.first;
		if (newStones.second != UINT64_MAX) {
			stones.insert_after(it, newStones.second);
			++it;
		}
	}
}

void day_main() {
	auto stones_arr = processInt("C:\\Users\\Keola\\dev\\c++\\AdventOfCode2024\\days\\day11\\input.txt");
	std::forward_list<uint64_t> stones;

	stones.push_front(stones_arr[0]);
	auto it = stones.begin();
	for (auto n : stones_arr) {
		stones.insert_after(it, n);
		++it;
	}
	stones.pop_front();

	std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> transformations;

	for (uint64_t i = 0; i < 75; ++i) {
		blink(stones, transformations);
	}

	int size = 0;
	for (auto it = stones.begin(); it != stones.end(); ++it) {
		++size;
	}

	printf("RESULT: %d", size);
}