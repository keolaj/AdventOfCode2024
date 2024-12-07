#include "day6.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

enum direction {
	up, right, down, left, wrong
};

struct state {
	int x;
	int y;
	direction dir;
	int map_size;

	bool operator==(const state& other) const {
		return x == other.x && y == other.y && dir == other.dir;
	}
	bool operator<(const state& other) const {
		return ((y * map_size) + x) * (int)dir < ((other.y * other.map_size) + other.x) * (int)other.dir;
	}
};

template <>
struct std::hash<state> {
	size_t operator()(const state& s) const {
		return ((s.y * s.map_size) + s.x) * (int)s.dir;
	}
};

direction next_dir(direction dir) {
	direction ret = static_cast<direction>((int)dir + 1);
	if (ret == wrong) {
		ret = up;
	}
	return ret;
}

state step(state current, const std::vector<std::string>& map) {
	state ret;
	ret.dir = current.dir;
	ret.map_size = current.map_size;

	int newx = current.x;
	int newy = current.y;
	switch (current.dir) {
	case up:
		--newy;
		break;
	case down:
		++newy;
		break;
	case left:
		--newx;
		break;
	case right:
		++newx;
		break;
	}
	if (newy < 0 || newy >= map.size() || newx < 0 || newx >= map.size()) {
		return { -1, -1, wrong };
	}
	else {
		if (map[newy][newx] == '.') {
			ret.x = newx;
			ret.y = newy;
		}
		else if (map[newy][newx] == '#') {
			ret.x = current.x;
			ret.y = current.y;
			ret.dir = next_dir(current.dir);
		}
	}
	return ret;
}

bool is_loop(state in, const std::unordered_set<state>& state_seen, const std::vector<std::string>& map) {
	state current = in;
	std::unordered_set<state> seen;
	seen.insert(in);
	while (true) {
		state next = step(current, map);
		if (next.x == -1 && next.y == -1) {
			return false;
		}
		if (seen.contains(next)) {
			return true;
		}
		seen.insert(next);
		current = next;
	}
}

std::pair<int, int> xy_from_int(int loc, int size) {
	std::pair<int, int> ret;
	ret.first = loc % size;
	ret.second = loc / size;
	return ret;
}

int make_loops(const std::vector<state>& states, const std::unordered_set<state>& state_seen, const std::unordered_set<int>& loc_seen, std::vector<std::string>& map) {
	int loops = 0;
	std::unordered_set<int> ob_locs;

	for (int i = 1; i < states.size(); ++i) {
		auto state = states[i];
		int hyp_obs = (state.y * state.map_size) + state.x;
		if (ob_locs.contains(hyp_obs)) continue;

		map[state.y][state.x] = '#';
		if (is_loop(states[i-1], state_seen, map)) {
			ob_locs.insert(hyp_obs);
			++loops;
		}
		map[state.y][state.x] = '.';
	}

	return loops;
}

void day_main() {
	std::ifstream input;
	input.open("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day6\\input.txt");
	if (!input.is_open()) {
		std::cout << "Couldn't open file!\n";
		return;
	}

	std::vector<std::string> map;
	std::string temp;
	while (std::getline(input, temp)) {
		map.push_back(temp);
	}

	int x, y = 0;
	char c;
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == '^' || map[i][j] == 'v' || map[i][j] == '<' || map[i][j] == '>') {
				x = j;
				y = i;
				c = map[i][j];
				goto end_loop;
			}
		}
	}
end_loop:
	map[y][x] = '.';
	direction dir;
	switch (c) {
	case '^':
		dir = up;
		break;
	case 'v':
		dir = down;
		break;
	case '<':
		dir = left;
		break;
	case '>':
		dir = right;
		break;
	default:
		dir = wrong;
		break;
	}
	state current{ x, y, dir, map.size() };

	int result = 1;
	
	std::unordered_set<int> seen;
	std::unordered_set<state> state_seen;
	std::vector<state> states;
	seen.insert(current.y * current.map_size + current.x);
	state_seen.insert(current);
	states.push_back(current);

	while (true) {
		state next = step(current, map);
		if (next.x == -1 && next.y == -1) break;
		int next_loc = next.y * map.size() + next.x;
		if (!seen.contains(next_loc)) {
			++result;
			seen.insert(next_loc);
		}
		state_seen.insert(next);
		states.push_back(next);
		current = next;
	}

	int loop_result = make_loops(states, state_seen, seen, map);

	std::cout << "RESULT: " << result << '\n';
	std::cout << "LOOP RESULT: " << loop_result << '\n';
}