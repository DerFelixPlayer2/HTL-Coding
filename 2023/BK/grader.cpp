#include "blinde-kuh.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

static int n, tx, ty, queries;
static long long ld = 1ll << 62;

static long long dist(int x, int y) {
	return (x - tx) * 1LL * (x - tx) + (y - ty) * 1LL * (y - ty);
}

int main() {
	std::cin >> n >> tx >> ty;
	blinde_kuh(n);
	std::cerr << "Target not found\n";
	return 1;
}

bool hit(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= n) {
		std::cerr << "Out of bounds queries\n";
		std::exit(1);
	}
	//std::cout << x << " " << y << std::endl;
	queries++;
	if (x == tx && y == ty) {
		//std::cout << "Y: " << y << std::endl;
		std::cout << "Done: " << queries << std::endl;
		std::exit(0);
	}
	auto d = dist(x, y);
	bool res = d < ld;
	ld = d;
	return res;
}