#include "shopping.h"

#include <algorithm>
#include <iostream>

#define INT_LENGTH 19
#define MAX_N (int)1e6

using namespace std;

// ALICE

int get_in_range(vector<int> p, const int l, const int r) {
	int s = INT32_MAX, si = -1;
	for (int i = l; i <= r; i++) {
		if (p[i] < s) {
			s = p[i];
			si = i;
		}
	}
	return si;
}

vector<int> _sort(const vector<int> &p, const int l, const int r) {
	vector<pair<int, int>> paired;
	paired.reserve((r - l) + 5);
	for (int i = l; i <= r; i++) {
		paired.push_back({p[i], i});
	}
	sort(paired.begin(), paired.end());
	vector<int> res((r - l) + 5);
	for (int i = 0; i < paired.size(); i++) res[i] = paired[i].second;
	return res;
}

void alice(vector<int> p) {
	int l = 0, r = p.size() - 1;
	for (int j = 0; j < 18; j++) {
		if (l > r) return;
		int i = get_in_range(p, l, r);
		send(i, 20);
		if (receive())
			r = i - 1;
		else
			l = i + 1;
	}

	auto sorted = _sort(p, l, r);
	for (int i = 0; i < sorted.size() && i * 20 + 360 < 500; i++)
		send(sorted[i], 20);
}

// BOB

// Send 0 if outside to the left
int bob(int n, int l, int r) {
	int guess;
	for (int i = 0; i < 18; i++) {
		guess = receive(20);
		if (guess <= r && guess >= l) {
			cout << "wasting " << (18 - i) << " guesses" << endl;
			send(INT32_MAX, 18 - i);
			return guess;
		}
		send(guess > r);
	}

	while ((guess = receive(20)) && (guess > r || guess < l))
		;

	return guess;
}
