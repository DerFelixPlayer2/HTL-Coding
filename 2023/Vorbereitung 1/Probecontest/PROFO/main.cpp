#include <iostream>
#include <vector>
#include <cstring>

#define MAX_M 2000

using namespace std;


int main() {
	ios_base::sync_with_stdio(false);

	int n, m, k, r;
	cin >> n >> m >> k >> r;

	// auto obstacles = new bool[n][MAX_M];
	auto dp = new long[n + 5][MAX_M + 5][2];
	memset(dp, 0, (n + 5) * (MAX_M + 5) * 2 * sizeof(long));

	for (int i = 0; i < r; i++) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;

		for (int y = y1; y <= y2; y++) dp[y - 1][x1 - 1][0] = -1;
		for (int x = x1; x <= x2; x++) dp[y1 - 1][x - 1][0] = -1;
	}

	for (int y = n - 1; y >= 0; y--) {
		for (int x = 0; x < m; x++) {
			if (dp[y][x][0] == -1) cout << "H ";
			else cout << dp[y][x][0] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int y = n - 1; y >= 0; y--) {
		for (int x = m - 1; x >= 0; x--) {
			if (dp[y][x][0] == -1 || (y == n - 1 && x == m - 1)) continue;
			else if ((y + 1 == n || dp[y + 1][x][0] == -1) && (dp[y][x + 1][0] == -1 || x + 1 == m)) dp[y][x][0] = 1;
			else if (dp[y + 1][x][0] == -1 || y + 1 == n) dp[y][x][0] = dp[y][x + 1][0] % 1000000007;
			else if (dp[y][x + 1][0] == -1 || x + 1 == m) dp[y][x][0] = dp[y + 1][x][0] % 1000000007;
			else dp[y][x][0] = (dp[y + 1][x][0] + dp[y][x + 1][0]) % 1000000007;
		}
	}

	for (int y = n - 1; y >= 0; y--) {
		for (int x = 0; x < m; x++) {
			if (dp[y][x][0] == -1) cout << "H ";
			else cout << dp[y][x][0] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << (dp[0][0][0] % 1000000007) << endl;
	delete[] dp;
}

// 4 4 4 2 3 2 3 3 2 3 3 3
// 4 5 3 2 3 3 3 4 2 4 3 4
// 10 10 0 5 10 1 10 10 3 2 3 3 2 3 3 3 6 5 6 6 5 6 6 6
// 5 5 0 1 5 1 5 5
// 6 6 0 2 2 2 4 4 6 1 6 6