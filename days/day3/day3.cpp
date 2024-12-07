#include "day3.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <stdint.h>

struct token {
	std::string symbol;
	char open;
	char close;
	std::vector<char> between_ok;
};

token mul = {
	"mul",
	'(',
	')',
	{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ','}
};
token _do = {
	"do",
	'(',
	')',
	{}
};
token _dont = {
	"don't",
	'(',
	')',
	{}
};

bool contains(std::vector<char> vec, char s) {
	for (char c : vec) {
		if (c == s) return true;
	}
	return false;
}

std::pair<int, int> ints_from_string(std::string s) {
	std::pair<int, int> ret;
	int first_begin = s.find_first_of("1234567890");
	int first_end = s.find_first_not_of("1234567890");
	std::string first_int = s.substr(first_begin, first_end - first_begin);
	ret.first = atoi(first_int.c_str());
	int second_begin = s.find_first_of("1234567890", first_end);
	int second_end = s.find_first_not_of("1234567890", second_begin);
	std::string second_int = s.substr(second_begin, second_end - second_begin);
	ret.second = atoi(second_int.c_str());
	return ret;
}

std::pair<int, int> first_token(std::vector<char> buf, std::vector<token> tokens, int start_index, std::string& out) {
	out.clear();
	int i = start_index;
	while (i != buf.size()) {
		for (int t = 0; t < tokens.size(); ++t) {
			auto token = tokens[t];
			std::pair<int, int> temp;
			for (int symbol_it = 0; symbol_it < token.symbol.size(); ++symbol_it) {
				if (symbol_it == 0) temp.first = i;
				if (buf[i + symbol_it] != token.symbol[symbol_it]) {
					if (t == tokens.size() - 1) goto cont_it;
					goto cont_token;
				}
			}
			if (buf[i + token.symbol.size()] == token.open) {
				int close_it = token.symbol.size() + 1;
				while (buf[i + close_it] != token.close) {
					if (i + close_it == buf.size()) {
						if (t == tokens.size() - 1) goto cont_it;
						goto cont_token;
					}
					if (contains(token.between_ok, buf[i + close_it])) {
						++close_it;
					}
					else {
						if (t == tokens.size() - 1) goto cont_it;
						goto cont_token;
					}
				}
				temp.second = i + close_it;
				for (int i = temp.first; i < temp.second + 1; ++i) {
					out += buf[i];
				}
				return temp;
			}
		cont_token:
			continue;
		}
	cont_it:
		++i;
		continue;
	}
	return { -1, -1 };
}

void day_main() {

	std::ifstream input;
	input.open("C:\\Users\\Keola\\dev\\c++\\adventofcode\\days\\day3\\input.txt");

	// create vector of chars from input.txt
	std::vector<char> in_buf;
	char c;
	while (input.get(c)) {
		in_buf.push_back(c);
	}
	in_buf.push_back('\0');

	// create vector of tokens to search for
	std::vector<token> tokens{ mul, _do, _dont };

	// vector for valid multiplication operation ranges
	std::vector<std::string> valid_muls;

	std::string out;
	std::pair<int, int> pair{0, 0};
	bool enabled = true;

	do {
		pair = first_token(in_buf, tokens, pair.second, out);
		if (out.contains("don't")) {
			enabled = false;
		}
		else if (out.contains("do")) {
			enabled = true;
		}
		else if (out.contains("mul")) {
			if (enabled) {
				valid_muls.push_back(out);
			}
		}
	} while (pair.first != -1);
	
	long long result = 0;
	for (auto s : valid_muls) {
		auto nums = ints_from_string(s);
		result += nums.first * nums.second;
	}
	std::cout << result;
}