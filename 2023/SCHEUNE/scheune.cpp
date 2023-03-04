#include "scheune.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>

#ifdef DEV
#define USE_LOGS
#define USE_POINTS
#define USE_VEC
#define USE_TIME
#endif

using namespace std;

bool hasTree(unordered_map<int, vector<int>> &_trees, const int r, const int c) {
	if (_trees[r].empty()) {
		return false;
	}
	if (_trees[r].size() == 1 && _trees[r][0] == c) {

#ifdef USE_POINTS
		cout << "Found Point{" << r << ", " << c << "}" << endl;
#endif

		return true;
	}

	int l = 0, h = (int) _trees[r].size() - 1;

	while (l <= h) {
		int m = (l + h) / 2;
		if (_trees[r][m] == c) {

#ifdef USE_POINTS
			cout << "Found Point{" << r << ", " << c << "}" << endl;
#endif

			return true;
		} else if (_trees[r][m] < c) {
			l = m + 1;
		} else {
			h = m - 1;
		}
	}

	return false;
}

int hasTree_AsNum(unordered_map<int, vector<int>> &_trees, const int r, const int c) {
	return hasTree(_trees, r, c) ? 0 : 1;
}

int solve(int n, const vector<Point> &trees) {
	if (n == 1) {
		return trees.empty() ? 1 : 0; // Should always be 0
	}

#if defined(USE_LOGS) || defined(USE_TIME)
	ios_base::sync_with_stdio(false);
#endif

	unordered_map<int, vector<int>> _trees;
	for (auto tree: trees) {
		_trees[tree.r].insert(upper_bound(_trees[tree.r].begin(), _trees[tree.r].end(), tree.c), tree.c);
		//_trees[tree.r].push_back(tree.c);
	}

	int max = 0;
#ifdef USE_VEC
	vector<int> cur(n), pre(n);
#else
	auto cur = (int *) malloc(sizeof(int) * n), pre = (int *) malloc(sizeof(int) * n);
#endif
#ifdef USE_TIME
	auto start = chrono::high_resolution_clock::now();
#endif

	// Top half
	for (int i = 1; i <= n; i++) {
		for (int j = i; j > 0; j--) {
			int c = i - j + 1, r = j;

			const int offset = n - j;
/*#ifdef USE_LOGS
			cout << "j: " << j << " i: " << i << " r: " << r << " c: " << c << " offset: " << offset << endl;
#endif/**/

			if (r == 1 || c == 1) {
				cur[offset] = hasTree_AsNum(_trees, r, c);
				if (cur[offset] > max) max = cur[offset];
			} else if (!hasTree(_trees, r, c)) {
				cur[offset] = min(cur[offset + 1], min(pre[offset], pre[offset + 1])) + 1;
				if (cur[offset] > max) max = cur[offset];
			} else {
				cur[offset] = 0;
			}

#ifdef USE_LOGS
			cout << cur[offset] << " " << max << endl;
#endif
		}

		auto tmp = cur;
		cur = pre;
		pre = tmp;
	}

	// Conversion row
	for (int j = n - 1; j > 0; j--) {
		int c = n - j + 1, r = 1 + j;

		const int offset = n - j;
/*#ifdef USE_LOGS
		cout << "j: " << j << " i: " << 1 << " r: " << r << " c: " << c << " offset: " << offset << endl;
#endif/**/

		if (r == 1 || c == 1) {
			cur[offset] = hasTree_AsNum(_trees, r, c);
			if (cur[offset] > max) max = cur[offset];
		} else if (!hasTree(_trees, r, c)) {
			cur[offset] = min(cur[offset], min(pre[offset], pre[offset - 1])) + 1;
			if (cur[offset] > max) max = cur[offset];
		} else cur[offset] = 0;

#ifdef USE_LOGS
		cout << cur[offset] << " " << max << endl;
#endif
	}

	auto tmp = cur;
	cur = pre;
	pre = tmp;

#ifdef USE_LOGS
	cout << "Now doing bottom half. Max: " << max << endl;
#endif

	// Bottom half
	for (int i = 2; i < n; i++) {
		for (int j = 1; j <= n - i; j++) {
			int c = n - j + 1, r = i + j;

			const int offset = n - j;
/*#ifdef USE_LOGS
			cout << "j: " << j << " i: " << i << " r: " << r << " c: " << c << " offset: " << offset << endl;
#endif/**/

			if (r == 1 || c == 1) {
				cur[offset] = hasTree_AsNum(_trees, r, c);
				if (cur[offset] > max) max = cur[offset];
			} else if (!hasTree(_trees, r, c)) {
				cur[offset] = min(cur[offset - 1], min(pre[offset], pre[offset - 1])) + 1;
				if (cur[offset] > max) max = cur[offset];
			} else cur[offset] = 0;

#ifdef USE_LOGS
			cout << cur[offset] << " " << max << endl;
#endif
		}

		tmp = cur;
		cur = pre;
		pre = tmp;
	}

#ifdef USE_TIME
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
#endif

	return max;
}


/*
 *
 * #include "scheune.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>

#ifdef DEV
#define USE_LOGS
#define USE_POINTS
#define USE_VEC
#define USE_TIME
#endif

using namespace std;

bool hasTree(unordered_map<int, vector<int>> &_trees, const int r, const int c) {
	if (_trees[r].empty()) {
		return false;
	}
	if (_trees[r].size() == 1 && _trees[r][0] == c) {

#ifdef USE_POINTS
		cout << "Found Point{" << r << ", " << c << "}" << endl;
#endif

		//_trees[r].clear();
		return true;
	}

	int l = 0, h = (int) _trees[r].size() - 1;

	while (l <= h) {
		int m = (l + h) / 2;
		if (_trees[r][m] == c) {
			//_trees[r].erase(next(_trees[r].begin(), m));

#ifdef USE_POINTS
			cout << "Found Point{" << r << ", " << c << "}" << endl;
#endif

			return true;
		} else if (_trees[r][m] < c) {
			l = m + 1;
		} else {
			h = m - 1;
		}
	}

	return false;
}

int hasTree_AsNum(unordered_map<int, vector<int>> &_trees, const int r, const int c) {
	return hasTree(_trees, r, c) ? 0 : 1;
}

int solve(int n, const vector<Point> &trees) {
	if (n == 1) {
		return trees.empty() ? 1 : 0; // Should always be 0
	}

#if defined(USE_LOGS) || defined(USE_TIME)
	ios_base::sync_with_stdio(false);
#endif

	unordered_map<int, vector<int>> _trees;
	for (auto tree: trees) {
		 _trees[tree.r].insert(upper_bound(_trees[tree.r].begin(), _trees[tree.r].end(), tree.c), tree.c);
		//_trees[tree.r].push_back(tree.c);
	}

	int max = 0;
#ifdef USE_VEC
	vector<int> cur(n), pre(n);
#else
	auto cur = (int *) malloc(sizeof(int) * n), pre = (int *) malloc(sizeof(int) * n);
#endif
#ifdef USE_TIME
	auto start = chrono::high_resolution_clock::now();
#endif

	// Top half
	for (int i = 1; i <= n; i++) {
		for (int j = i; j > 0; j--) {
			int c = i - j + 1, r = j;

			const int offset = n - j;
#ifdef USE_LOGS
			cout << "j: " << j << " i: " << i << " r: " << r << " c: " << c << " offset: " << offset << endl;
#endif

if (r == 1 || c == 1) {
cur[offset] = hasTree_AsNum(_trees, r, c);
if (cur[offset] > max) max = cur[offset];
} else if (!hasTree(_trees, r, c)) {
cur[offset] = min(cur[offset + 1], min(pre[offset], pre[offset + 1])) + 1;
if (cur[offset] > max) max = cur[offset];
} else {
cur[offset] = 0;
}

#ifdef USE_LOGS
cout << cur[offset] << " " << max << endl;
#endif
}

auto tmp = cur;
cur = pre;
pre = tmp;
}

// Conversion row
for (int j = n - 1; j > 0; j--) {
int c = n - j + 1, r = 1 + j;

const int offset = n - j;
#ifdef USE_LOGS
		cout << "j: " << j << " i: " << 1 << " r: " << r << " c: " << c << " offset: " << offset << endl;
#endif

if (r == 1 || c == 1) {
cur[offset] = hasTree_AsNum(_trees, r, c);
if (cur[offset] > max) max = cur[offset];
} else if (!hasTree(_trees, r, c)) {
cur[offset] = min(cur[offset], min(pre[offset], pre[offset - 1])) + 1;
if (cur[offset] > max) max = cur[offset];
} else cur[offset] = 0;

#ifdef USE_LOGS
cout << cur[offset] << " " << max << endl;
#endif
}

auto tmp = cur;
cur = pre;
pre = tmp;

#ifdef USE_LOGS
cout << "Now doing bottom half. Max: " << max << endl;
#endif

// Bottom half
for (int i = 2; i < n; i++) {
for (int j = 1; j <= n - i; j++) {
int c = n - j + 1, r = i + j;

const int offset = n - j;
#ifdef USE_LOGS
			cout << "j: " << j << " i: " << i << " r: " << r << " c: " << c << " offset: " << offset << endl;
#endif

if (r == 1 || c == 1) {
cur[offset] = hasTree_AsNum(_trees, r, c);
if (cur[offset] > max) max = cur[offset];
} else if (!hasTree(_trees, r, c)) {
cur[offset] = min(cur[offset - 1], min(pre[offset], pre[offset - 1])) + 1;
if (cur[offset] > max) max = cur[offset];
} else cur[offset] = 0;

#ifdef USE_LOGS
cout << cur[offset] << " " << max << endl;
#endif
}

tmp = cur;
cur = pre;
pre = tmp;
}

#ifdef USE_TIME
auto end = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
#endif

return max;
}
 * */