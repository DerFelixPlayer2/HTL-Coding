#include "hanoi.h"

int N(int a, int b) {
	return a != 1 && b != 1 ? 1 : a != 2 && b != 2 ? 2 : 3;
}

void m(int n, int from, int to) {
	if (n == 1) {
		move(from, to);
	} else {
		m(n - 1, from, N(from, to));
		move(from, to);
		m(n - 1, N(from, to), to);
	}
}

void hanoi(int n) {
	m(n, 1, 2);
}

