#include "starter.h"
#include <iostream>

int subtask1(int a, int b) {
	return a + b;
}

int subtask2(int n) {
	int c = 0;
	for (int i = 0; i <= n; i++) {
		c += i;
	}
	return c;
}

bool req_bin_search(std::vector<int> &v, int x, size_t current, size_t low, size_t high) {
	std::cout << current << " " << v.at(current) << " " << low << " " << high << " " << std::endl;
	if (v.at(current) == x) {
		return true;
	} else if (high - low <= 1) {
		return false;
	}

	if (v.at(current) > x) {
		return req_bin_search(v, x, current - (current - low) / 2, low, current);
	} else {
		return req_bin_search(v, x, current + (high - current) / 2, current, high);
	}
}

bool subtask3(std::vector<int> &v, int x) {
	std::cout << x << std::endl;
	return req_bin_search(v, x, v.size() / 2, 0, v.size());
}

