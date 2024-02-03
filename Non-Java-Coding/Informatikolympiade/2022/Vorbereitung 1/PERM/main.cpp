#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> v;

void permutations(int n) {
	if (n == 1) {
		for (int i: v)
			cout << i << " ";
		cout << endl;
	} else {
		for (int i = 1; i <= n; i++) {
			swap(v[i - 1], v[n - 1]);
			permutations(n - 1);
			swap(v[i - 1], v[n - 1]);
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		v.push_back(i + 1);
	permutations(n);
}
