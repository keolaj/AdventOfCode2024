#include "day9.h"
#include "../helpers.h"
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <chrono>

std::vector<int> processInt(const char* path) {
	std::vector<int> map;
	std::ifstream input{ path };
	if (!input.is_open()) {
		std::cout << "couldn't open file\n";
		return map;
	}
	char c;
	while (true) {
		input.get(c);
		if (input.eof()) break;
		map.push_back(c - '0');
	}
	return map;

}

std::vector<int> createFs(std::vector<int> map) {
	std::vector<int> ret;
	int id = 0;
	if (map.size() % 2 != 0) map.push_back(0);
	for (int i = 0; i < map.size(); i += 2) {
		int fileSize = map[i];
		for (int fileCount = 0; fileCount < map[i]; ++fileCount) {
			ret.push_back(id);
		}
		++id;
		for (int freeCount = 0; freeCount < map[i + 1]; ++freeCount) {
			ret.push_back(-1);
		}
	}
	return ret;
}

void processFs(std::vector<int>& fs) {
	std::queue<int> freeLocs;
	for (int i = 0; i < fs.size(); ++i) {
		if (fs[i] == -1) {
			freeLocs.push(i);
		}
	}
	int index = fs.size() - 1;
	while (freeLocs.size() != 0) {
		int emptyIndex = freeLocs.front();
		freeLocs.pop();

		while (fs[index] == -1) --index;

		fs[emptyIndex] = fs[index];
		fs[index] = -1;
		--index;
	}
	for (int i = 0; i < fs.size(); ++i) {
		if (fs[i] == -1) {
			freeLocs.push(i);
		}
	}
	index = fs.size() - 1;
	while (true) {
		int emptyIndex = freeLocs.front();
		freeLocs.pop();

		while (fs[index] == -1) {
			if (index == emptyIndex) return;
			--index;
			if (index == emptyIndex) return;
		}

		fs[emptyIndex] = fs[index];
		fs[index] = -1;
		--index;
	}
}

struct file {
	int id;
	int size;
	int freeSize;
	int origSize;
};

void processFs2(std::vector<int>& fs, std::vector<int> map) { // I don't have time to optimize this today I have finals to study for
	std::vector<file> intermediate;
	int id = 0;
	if (map.size() % 2 != 0) map.push_back(0);
	for (int i = 0; i < map.size(); i += 2) {
		int fileSize = map[i];
		int freeSize = map[i + 1];
		intermediate.push_back({ id, fileSize, freeSize, fileSize });
		++id;
	}
	for (int i = intermediate.size() - 1; i >= 0; --i) {
		file& transfer = intermediate[i];
		for (int j = 0; j < intermediate.size(); ++j) {
			if (j >= i) break;
			file& transferTo = intermediate[j];
			if (transferTo.freeSize >= transfer.origSize) {
				int freeIndex = -1;
				for (int l = 0; l < fs.size(); ++l) {
					if (fs[l] == transferTo.id) {
						freeIndex = l + transferTo.size;
						break;
					}
				}
				int transferIndex = -1;
				for (int m = fs.size() - 1; m >= 0; --m) {
					if (fs[m] == transfer.id) {
						transferIndex = m;
						break;
					}
				}
				for (int k = 0; k < transfer.origSize; ++k) {
					fs[freeIndex++] = transfer.id;
					fs[transferIndex--] = -1;
				}
				transferTo.size += transfer.origSize;
				transferTo.freeSize -= transfer.origSize;
				break;
			}
		}
	}
}

uint64_t checksum(std::vector<int> fs) {
	uint64_t ret = 0;
	for (int i = 0; i < fs.size(); ++i) {
		if (fs[i] == -1) continue;
		ret += fs[i] * i;
	}
	return ret;
}

void day_main() {
	auto map = processInt("C:\\Users\\Keola\\dev\\c++\\AdventOfCode2024\\days\\day9\\input.txt");
	auto fs = createFs(map);
	auto start = std::chrono::high_resolution_clock::now();
	processFs2(fs, map);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("RESULT: %lld %lldms", checksum(fs), duration);
}