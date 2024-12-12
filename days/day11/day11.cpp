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

struct PairHash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);
		return std::rotl(h1, 1) ^ h2;
	}
};

struct PairEqual {
	template <class T1, class T2>
	bool operator () (const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const {
		return p1.first == p2.first && p1.second == p2.second;
	}
};

uint64_t blinkStone(uint64_t stone, std::unordered_map<std::pair<uint64_t, uint64_t>, uint64_t, PairHash, PairEqual>& transform_count, uint64_t count) {
	if (count == 0) {
		return 1;
	}
	if (stone == 0) {
		if (transform_count.contains({ stone, count })) return transform_count[{stone, count}];
		else {
			auto c = blinkStone(1, transform_count, count - 1);
			transform_count[{stone, count}] = c;
			return c;
		}
	}
	else {
		if (transform_count.contains({ stone, count })) return transform_count[{stone, count}];
		uint64_t power = 0;
		for (uint64_t i = stone; i != 0; i /= 10) {
			++power;
		}
		if (power % 2 == 0) {
			uint64_t higher = stone / (exp(10, power / 2));
			uint64_t lower = stone - (higher * (exp(10, power / 2)));

			auto c = blinkStone(higher, transform_count, count - 1) + blinkStone(lower, transform_count, count - 1);
			transform_count[{stone, count}] = c;
			return c;
		}
		else {
			auto c = blinkStone(stone * 2024, transform_count, count - 1);
			transform_count[{stone, count}] = c;
			return c;
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

	std::unordered_map<std::pair<uint64_t, uint64_t>, uint64_t, PairHash, PairEqual> transform_count;
	
	uint64_t size = 0;
	for (auto stone : stones_arr) {
		size += blinkStone(stone, transform_count, 75);
	}

	std::cout << size;
}