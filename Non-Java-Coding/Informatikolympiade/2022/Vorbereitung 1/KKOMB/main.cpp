#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> v;

void kkomb(int n, int k) {
	if (k == 0) {
		for (int i: v)
			cout << i << " ";
		cout << "\n";
	} else if (n != 0) {
		v.push_back(n);
		kkomb(n - 1, k - 1);
		v.pop_back();
		kkomb(n - 1, k);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int n, k;
	cin >> n;
	cin >> k;

	if (k <= n) kkomb(n, k);
}