#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> res;

void p(int i) {
	//cout << "pushing " << i << endl;
	res.push_back(i);
}

void recursive_fill_res(int lower_bound, int higher_bound) {
	cout << lower_bound << " " << higher_bound << endl;
	if (lower_bound >= higher_bound) p(lower_bound);
	else {
		int mid = (higher_bound + lower_bound) / 2;
		if (mid == lower_bound) {
			p(lower_bound);
			p(higher_bound);
			return;
		}
		p(mid);
		recursive_fill_res(lower_bound, mid - 1);
		recursive_fill_res(mid + 1, higher_bound);
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	while (true) {
		res.clear();

		int n, k, i;
		cin >> n >> k;

		if (k > n || pow(2, k) < n) {
			cout << -1 << endl;
			continue;
			//return 0;
		}

		res.reserve(n);
		for (i = 0; ++i <= k;) p(i);

		if (i - 1 < n) recursive_fill_res(i, n);

		cout << n << " " << k << ":" << endl;
		for (int j = 0; j < n; j++) cout << res[j] << " ";
		cout << endl;
	}
	return 0;
}
