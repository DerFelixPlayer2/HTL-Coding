#include <cstdio>
#include <ctime>

#include "scheune.h"

using namespace std;

int main() {
	int n, k;
	/*scanf("%d", &n);
	vector<Point> v(std::min(n * n, 10000));
	int l = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if ((i * n) + j > 10000) break;
			v[l].r = i;
			v[l++].c = j;
		}
	}*/
	srand(time(nullptr));
	while (true) {
		scanf("%d %d", &n, &k);

		if (k < 0) {
			vector<Point> v(-k);
			int l = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if (((i - 1) * n) + j > -k) goto _do;
					v[l].r = i;
					v[l++].c = j;
				}
			}
			_do:
			int res = solve(n, v);
			printf("%d\n", res);
		} else {
			vector<Point> v(k);
			for (auto &x: v) scanf("%d %d", &x.r, &x.c);
			int res = solve(n, v);
			printf("%d\n", res);
		}
	}

	return 0;
}
