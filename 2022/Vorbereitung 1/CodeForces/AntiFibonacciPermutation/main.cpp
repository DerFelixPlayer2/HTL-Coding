#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool works(vector<int> &v) {
	for (int i = 2; i < v.size(); i++) {
		if (v[i] == v[i - 1] + v[i - 2]) {
			return false;
		}
	}
	return true;
}

int amt, N;

void calc(int n, vector<int> &v) {
	if (amt >= N) return;
	if (n == 1) {
		if (works(v)) {
			amt++;
			for (int i: v)
				cout << i << " ";
			cout << "\n";
		}
	} else {
		for (int i = 1; i <= n; i++) {
			swap(v[i - 1], v[n - 1]);
			calc(n - 1, v);
			swap(v[i - 1], v[n - 1]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);

	int cases;
	cin >> cases;

	for (int i = 0; i < cases; ++i) {
		int n;
		cin >> n;

		vector<int> v(n);
		for (int j = 0; j < n; ++j)
			v[j] = j + 1;
		amt = 0;
		N = n;

		calc(n, v);
	}
}
