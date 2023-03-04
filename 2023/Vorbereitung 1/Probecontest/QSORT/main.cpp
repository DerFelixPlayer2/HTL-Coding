#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> res;

template<class Iterator>
int quicksort(Iterator bgn, Iterator end) {
	if (bgn == end)
		return 0;
	int p = *bgn;
	auto mid = std::stable_partition(bgn, end, [p](int x) {
		return x < p;
	});
	return 1 + std::max(quicksort(bgn, mid),
						quicksort(mid + 1, end));
}

int s(vector<int> v) {
	return quicksort(v.begin(), v.end());
}

void p(int i) {
	//cout << "pushing " << i << endl;
	res.push_back(i);
}

void recursive_fill_res(int lower_bound, int higher_bound) {
	//cout << lower_bound << " " << higher_bound << endl;
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

	// cout << "t " << s({2, 1, 4, 3}) << endl;

	int n, k, i;
	cin >> n >> k;

	if (k > n || pow(2, k) <= n) {
		cout << -1 << endl;
		return 0;
	}

	res.reserve(n);
	for (i = 1; i + log2(n - i) < k;) p(i++);

	if (i - 1 < n) recursive_fill_res(i, n);

	for (int j = 0; j < n; j++) cout << res[j] << " ";
	cout << endl;

	return 0;
}
