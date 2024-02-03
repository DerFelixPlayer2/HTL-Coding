#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> res;

void recursive_fill_res(int lower_bound, int higher_bound) {
	if (lower_bound >= higher_bound) res.push_back(lower_bound);
	else {
		int mid = (higher_bound + lower_bound) / 2;
		if (mid == lower_bound) {
			res.push_back(lower_bound);
			res.push_back(higher_bound);
			return;
		}
		res.push_back(mid);
		recursive_fill_res(lower_bound, mid - 1);
		recursive_fill_res(mid + 1, higher_bound);
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	int n, k, i;
	cin >> n >> k;

	if (k > n || pow(2, k) <= n) {
		cout << -1 << endl;
		return 0;
	}

	res.reserve(n);
	for (i = 1; i + log2(n - i) < k;) res.push_back(i++);

	if (i - 1 < n) recursive_fill_res(i, n);

	for (int j = 0; j < n; j++) cout << res[j] << " ";
	cout << endl;

	return 0;
}
