#include <iostream>
#include <bits/stdc++.h>

#define max(a, b) (a > b ? a : b)

#define NO -9999999

using namespace std;


// Let f(k) be the maximum sum of a contiguous subarray after adding x to k distinct elements
// Calculate the maximum value of f(k) for all k from 0 to n independently
// f(k) = max(f(k-1) + x, x)
int maxSubArray(vector<int> &v, int from, int to) {
	if (from == to) {
		cout << "(maxsub1) from-to: " << from << " " << to << endl;
		cout << "(maxsub1) value: " << v[from] << endl;
		cout << "(maxsub1) v1: " << (max(v[from], 0) == 0 ? NO : v[from]) << endl;
		return (max(v[from], 0) == 0 ? NO : v[from]);
	}

	cout << "(maxsub2) from-to: " << from << " " << to << endl;
	cout << "(maxsub2) value: " << v[from] << endl;
	cout << "(maxsub2) v1: " << (max(v[from], 0) == 0 ? NO : v[from]) << endl;
	cout << "(maxsub2) v2: " << (maxSubArray(v, from + 1, to) + v[from]) << endl;

	return max(maxSubArray(v, from, to - 1), (maxSubArray(v, from + 1, to) + v[from]));
}

int calc(int n, int k, int x, vector<int> &items) {

	if (k == 0) {

		cout << 0 << endl;
		cout << maxSubArray(items, 0, n) << endl;
		cout << max(0, maxSubArray(items, 0, n)) << endl;

		return max(0, maxSubArray(items, 0, n));
	}

	return max(maxSubArray(items, 0, n), maxSubArray(items, 0, n) + (k * x));
}

int main() {
	int cases;
	std::cin >> cases;

	for (int i = 0; i < cases; i++) {
		int n, x;
		std::cin >> n >> x;

		vector<int> v(n);
		for (int j = 0; j < n; j++) {
			std::cin >> v[j];
		}

		for (int j = 0; j <= n; j++) {
			printf("%d: %d %d %d ", calc(n, j, x, v), n, j, x);
			//int r = calc(n, j, x, v);
			//cout << to_string(r) << " ";
		}
		cout << "\n";


	}
}
