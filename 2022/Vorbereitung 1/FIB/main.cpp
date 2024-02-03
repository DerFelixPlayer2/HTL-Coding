#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

using namespace std;

int main() {
	__int128_t n = 0, i = 0, c = 1, p = 1, pp;

	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		__int128_t d = s[i] - 48;
		n += d * pow(10, (s.length() - i - 1));
	}

	vector<int> r;
	for (; n >= 10; n /= 10) {
		cout << int(n % (__int128_t)10) << " ";
		r.push_back(n % (__int128_t)10);
	}
	r.push_back(n);
	for (int n = r.size() - 1; n >= 0; n--) cout << r[n];
	cout << endl;

	return 0;

	for (i = 0; i < n; i++) {
		pp = p;
		p = c;
		c = (c + pp) % MOD;
	}

	int64_t shortened = n % (i + 1);
	for (i = 0, c = 1, p = 0; i < shortened; i++) {
		pp = p;
		p = c;
		c = (c + pp) % MOD;
	}

	// vector<int> r;
	for (; p >= 10; p /= 10) r.push_back(p % 10);
	r.push_back(p);
	for (int n = r.size() - 1; n >= 0; n--) cout << r[n];
	cout << endl;

	return 0;
}