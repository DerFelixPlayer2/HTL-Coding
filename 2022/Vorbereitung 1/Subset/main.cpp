#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void subset(int n, vector<int> &v) {
	if (n == 0) {
		for (int e: v)
			cout << e << " ";
		cout << "\n";
	} else {
		subset(n - 1, v);
		v.push_back(n);
		subset(n - 1, v);
		v.pop_back();
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> v;
	subset(n, v);
}