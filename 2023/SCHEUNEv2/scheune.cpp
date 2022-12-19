#include "scheune.h"

#ifdef DEV
//#define USE_LOGS
#define USE_VEC
#define USE_TIME
#endif

#if defined(USE_LOGS) || defined(USE_TIME)
#include <iostream>
#endif

#ifdef USE_TIME
#include <chrono>
#endif

using namespace std;

bool hasTree(vector<Point> &_trees, const int r, const int c) {
	int l = 0, h = (int) _trees.size() - 1;

	while (l <= h) {
		int m = (l + h) / 2;
		if (_trees[m].r == r && _trees[m].c == c) {
			_trees.erase(next(_trees.begin(), m));

#ifdef USE_LOGS
			cout << "Found Point{" << r << ", " << c << "}" << endl;
#endif

			return true;
		} else if (_trees[m].r < r || (_trees[m].r == r && _trees[m].c < c)) {
			l = m + 1;
		} else {
			h = m - 1;
		}
	}

	return false;
}

int solve(int n, const vector<Point> &trees) {
	if (n == 1) {
		return trees.empty() ? 1 : 0; // Should always be 0
	}

#if defined(USE_LOGS) || defined(USE_TIME)
	ios_base::sync_with_stdio(false);
#endif

	vector<Point> _trees(trees.size());
	copy(trees.begin(), trees.end(), _trees.begin());
	sort(_trees.begin(), _trees.end(), [](const Point &a, const Point &b) {
		return a.r == b.r ? a.c < b.c : a.r < b.r;
	});

	int max = 0;
#ifdef USE_VEC
	vector<int> h(n), v(n);
	vector<int> v2(n - 1), h2(n - 1);
#else
	auto h = (int *) malloc(sizeof(int) * n), v = (int *) malloc(sizeof(int) * n);
	int *v2 = (int *) malloc(sizeof(int) * n), *h2 = (int *) malloc(sizeof(int) * n);
#endif
#ifdef USE_TIME
	auto start = chrono::high_resolution_clock::now();
#endif

	v[0] = hasTree(_trees, 1, 1) ? 0 : 1;
	h[0] = v[0];
	if (h[0] == 1) max = 1;
	for (int i = 1; i < n; i++) {
		v[i] = hasTree(_trees, i + 1, 1) ? 0 : 1;
		h[i] = hasTree(_trees, 1, i + 1) ? 0 : 1;
		if (v[i] == 1 || h[i] == 1) max = 1;
	}

#ifdef USE_TIME
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
	start = chrono::high_resolution_clock::now();
#endif

	for (int i = 1; i < n; i++) {
		if (!hasTree(_trees, i + 1, i + 1)) {
			v2[0] = min(v[1], min(h[1], h[0])) + 1;
			h2[0] = v2[0];
			if (v2[0] > max) max = v2[0];
		} else {
			v2[0] = 0;
			h2[0] = 0;
		}

		for (int j = 1; j < n - i; j++) {
			if (!hasTree(_trees, j + 1 + i, i + 1)) {
				v2[j] = min(v2[j - 1], min(v[j], v[j + 1])) + 1;
				if (v2[j] > max) max = v2[j];
			} else v2[j] = 0;
			if (!hasTree(_trees, i + 1, j + 1 + i)) {
				h2[j] = min(h2[j - 1], min(h[j], h[j + 1])) + 1;
				if (h2[j] > max) max = h2[j];
			} else h2[j] = 0;
		}

		auto tmp = v;
		v = v2;
		v2 = tmp;
		tmp = h2;
		h2 = h;
		h = tmp;
	}

#ifdef USE_TIME
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
#endif

	return max;
}
