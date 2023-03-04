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

constexpr inline int min(const int &a, const int &b, const int &c, const int &d) {
	return min(min(a, b), min(c, d));
}

constexpr inline int max(const int &a, const int &b, const int &c, const int &d) {
	return max(max(a, b), max(c, d));
}

bool hasTree(const int n, unordered_map<int, vector<int>> &trees, const int &r1, const int &c1, const int &r2,
			 const int &c2) {
	if (min(r1, r2, c1, c2) < 0 || max(r1, r2, c1, c2) > n + 1) return true;

	for (int r = min(r1, r2) + 1; r < max(r1, r2); r++) {
		if (trees[r].empty()) {
			//cout << "e ";
			continue;
		}
		if (trees[r].size() == 1 && trees[r][0] < max(c1, c2) && trees[r][0] > min(c1, c2)) {
			//cout << "o ";
			return true;
		}

		int l = 0, h = (int) trees[r].size() - 1;

		while (l <= h) {
			int m = (l + h) / 2;
			if (trees[r][m] < max(c1, c2) && trees[r][m] > min(c1, c2)) {
				//cout << "s ";
				return true;
			} else if (trees[r][m] < max(c1, c2)) {
				l = m + 1;
			} else {
				h = m - 1;
			}
		}
	}

	return false;
}

int solve(int n, const vector<Point> &_trees) {
	if (n == 1) {
		return _trees.empty() ? 1 : 0; // Should always be 0
	}

#if defined(USE_LOGS) || defined(USE_TIME)
	ios_base::sync_with_stdio(false);
#endif

	unordered_map<int, vector<int>> trees;
	trees[0].insert(upper_bound(trees[0].begin(), trees[0].end(), 0), 0);
	trees[0].insert(upper_bound(trees[0].begin(), trees[0].end(), n + 1), n + 1);
	trees[n + 1].insert(upper_bound(trees[n + 1].begin(), trees[n + 1].end(), 0), 0);
	trees[n + 1].insert(upper_bound(trees[n + 1].begin(), trees[n + 1].end(), n + 1), n + 1);
	for (auto tree: _trees) {
		trees[tree.r].insert(upper_bound(trees[tree.r].begin(), trees[tree.r].end(), tree.c), tree.c);
	}


	int largest = 0;

#ifdef USE_TIME
	auto start = chrono::high_resolution_clock::now();
#endif

	for (const auto &t1: trees) {
		for (const auto &t2: trees) {
			// if (j <= i) continue;

			const int r1 = t1.first;
			const int r2 = t2.first;

			const int dr = abs(r1 - r2);
			for (const int &c1: t1.second) {
				for (const int &c2: t2.second) {
					const int dc = abs(c1 - c2);
					int sc = dc;
					int sr = dr;

					if (dr > dc) {
						sr--;
						sc++;
					} else if (dc > dr) {
						sr++;
						sc--;
					} else {
						sr--;
						sc--;
					}


					if (sc != sr) {
						continue;
					} else {
						if (dr > dc) {
							for (int c = min(c1, c2); c <= max(c1, c2); c++) {
								if (!hasTree(n, trees, min(r1, r2), c, min(r1, r2) + sc + 1, c + sc + 1)) {
									largest = max(dc, largest);
								}
							}
						} else if (dc > dr) {
							for (int r = max(r1, r2) - 1; r >= min(r1, r2) + 1; r--) {
								if (!hasTree(n, trees, r, min(c1, c2), r + sc + 1, min(c1, c2) + sc + 1)) {
									largest = max(dr, largest);
								}
							}
						} else {
							if (!hasTree(n, trees, r1, c1, r2, c2)) {
								largest = max(dr, largest);
							}
						}
					}
/*
					if (dc > dr) {
						for (int i = r1 - dc; i <= r1 + dc; i++) {
							if (!hasTree(n, trees, r1, c1, i, c2)) {
								largest = std::largest(dc, largest);
							}
						}
					} else if (dr > dc) {
						for (int i = c1 - dr; i <= c1 + dr; i++) {
							if (!hasTree(n, trees, r1, c1, r1, i)) {
								largest = std::largest(dr, largest);
							}
						}
					} else {




						if (!hasTree(n, trees, r1, c1, r2, c2)) {
							largest = std::largest(dr, largest);
						}
					}*/
				}
			}
		}
	}

#ifdef USE_TIME
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
#endif

	return largest;
}
