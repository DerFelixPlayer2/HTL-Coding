#include "ISUM.h"
#include <iostream>

using namespace std;

#ifdef DEV
#define PRINT
#endif

int *st;
int *lazy;
int n;

void create_segment_tree() {
	lazy = new int[2 * n];
	st = new int[2 * n];
	for (int i = 0; i < n; i++) {
		st[n + i] = 0;
		lazy[n + i] = 0;
	}
	for (int i = n - 1; i > 0; --i) {
		st[i] = 0;
		lazy[i] = 0;
	} // st[i << 1] + st[i << 1 | 1];
}

void update_value(int i, int new_val) {
	st[n + i] = new_val;
	for (int j = (n + i) >> 1; j > 0; j >>= 1) st[j] = st[j << 1] + st[j << 1 | 1];
}

long long get_sum_in_range(int s, int e) {
	long long sum = 0;
	for (s += n, e += n; s < e; s >>= 1, e >>= 1) {
		if (s & 1) sum += st[s++];
		if (e & 1) sum += st[--e];
	}
	return sum;
}

void add_value(int i, int inc) {
	update_value(i, st[n + i] + inc);
}

void print_t() {
#ifdef PRINT
	cout << "tree: ";
	for (int i = 0; i < 2 * n; i++) cout << st[i] << " ";
	cout << endl;
#endif
}

void init(int N) {
	// cout << "Init" << endl;
	// ios_base::sync_with_stdio(false);

	n = N;
	create_segment_tree();
	print_t();
}

void update(int p, int q, int v) {
	// cout << "Update" << endl;
	for (int i = min(p, q) - 1; i < max(p, q); i++) {
		add_value(i, v);
	}
	print_t();
}

long long query(int p, int q) {
	// cout << "Query" << endl;
	return get_sum_in_range(min(p, q) - 1, max(p, q));
}

