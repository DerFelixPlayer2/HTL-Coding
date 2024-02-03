#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v;
	v.reserve(n);
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		v.push_back(k);
	}

	sort(v.begin(), v.end());

	for (auto val : v) cout << val << " ";
	cout << endl;

	return 0;
}