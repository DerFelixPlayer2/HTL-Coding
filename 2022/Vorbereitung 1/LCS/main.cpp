#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int SIZE = 1005;
int dp[SIZE][SIZE];

int main() {
	string str1, str2, ans = "";
	cin >> str1 >> str2;

	dp[0][0] = 0;
	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
	}
	cout << dp[str1.length()][str2.length()] << "\n";

	size_t i = str1.length(), j = str2.length();
	while (i != 0 && j != 0) {
		if (str1[i - 1] == str2[j - 1]) {
			ans += str1[i - 1];
			i--;
			j--;
		} else {
			if (dp[i - 1][j] > dp[i][j - 1]) {
				i--;
			} else j--;
		}
	}

	for (i = ans.length(); i > 0; i--)
		cout << ans[i - 1];
	cout << "\n";
}
