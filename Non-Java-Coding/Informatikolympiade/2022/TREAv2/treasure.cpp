#include "treasure.h"

#include <cstring>
#include <cmath>
#include <iostream>

int getNumberOfTreasuresInArea(int **map, int r2, int c2);
void findTreasure(int **map, int n, int r2, int c2, int max_treasure, int *found);
int getNumberOfTreasuresInAreaAfterMaximizing(int **map, int N, int r1, int c1, int r2, int c2);

void findTreasure(int N) {

	auto map = (int **) calloc(N, sizeof(int *));
	for (int i = 0; i < N; i++) {
		map[i] = (int *) calloc(N, sizeof(int));
		memset(map[i], -1, N * sizeof(int));
	}

	int found = 0, t = getNumberOfTreasuresInArea(1, 1, N, N);
	findTreasure(map, N, 1, 1, t, &found);

	for (int i = 0; i < N; i++)
		free(map[i]);
	free(map);
}

void findTreasure(int **map, const int n, const int r2, const int c2, const int max_treasure, int *found) {
	if (r2 > n || c2 > n) return;
	if (map[r2 - 1][c2 - 1] != -1) return;
	if (*found == max_treasure) return;
	if (max_treasure == 1 && n == 1) {
		reportTreasure(1, 1);
		return;
	}

	//int t = treasure == -1 ? getNumberOfTreasuresInArea(map, r2, c2) : treasure;
	//int t = treasure == -1 ? getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, c2) : treasure;
	int t = getNumberOfTreasuresInArea(map, r2, c2);
	//int t = getNumberOfTreasuresInAreaAfterMaximizing(map, n, 1, 1, r2, c2);
	if (t == -1) {
		return;
	} else if (t == 0) {
		map[r2 - 1][c2 - 1] = 0;
	} else if (t == 1) {
		map[r2 - 1][c2 - 1] = 1;
		reportTreasure(r2, c2);
		(*found)++;
	} else {
		printf("%d: WEIRD\n", n);
	}


	findTreasure(map, n, r2 + 1, c2, max_treasure, found);
	findTreasure(map, n, r2, c2 + 1, max_treasure, found);
	return;

	/*int mc, mr, t0 = 0;

	/*if (n <= 4) {
		mr = r1 + ((r2 - r1) / 2);
		mc = c1 + ((c2 - c1) / 2);

		if (r2 - r1 > c2 - c1) {
			t0 += findTreasure(map, n, r1, c1, mr, c2); // top
			t0 += findTreasure(map, n, mr + 1, c1, r2, c2, t - t0); // bottom
		} else {
			t0 += findTreasure(map, n, r1, c1, r2, mc); // left
			t0 += findTreasure(map, n, r1, mc + 1, r2, c2, t - t0); // right
		}

		return t0;
	}

	/*{    // coll
		int rem = (c2 - c1 + 1) % 4;
		int a = floor(((double) (c2 - c1 + 1)) / 4);
		int b = 4;
		switch (rem) {
			case 1:
				b++;
				break;
			case 2:
				b++;
				a++;
				break;
			case 3:
				b += 2;
				a++;
			default:
				break;
		}
		mc = c1 + b;
	}

	{    // row
		int rem = (r2 - r1 + 1) % 4;
		int a = floor(((double) (r2 - r1 + 1)) / 4);
		int b = 4;
		switch (rem) {
			case 1:
				b++;
				break;
			case 2:
				b++;
				a++;
				break;
			case 3:
				b += 2;
				a++;
			default:
				break;
		}
		mr = r1 + b;
	}*/

	/*mr = r2 - (int) ceil((double) (r2 - r1) / 2.5);
	mc = c2 - (int) ceil((double) (c2 - c1) / 2.5);*/

	/*if (r2 - r1 > c2 - c1) {
		t0 += findTreasure(map, n, mr + 1, c1, r2, c2); // bottom
		findTreasure(map, n, r1, c1, mr, c2, t - t0); // top
	} else {
		t0 += findTreasure(map, n, r1, mc + 1, r2, c2); // right
		findTreasure(map, n, r1, c1, r2, mc, t - t0); // left
	}*/

	/*if (r2 - r1 > c2 - c1) {
		t0 += findTreasure(map, n, r1, c1, mr, c2); // top
		findTreasure(map, n, mr + 1, c1, r2, c2, t - t0); // bottom
	} else {
		t0 += findTreasure(map, n, r1, c1, r2, mc); // left
		findTreasure(map, n, r1, mc + 1, r2, c2, t - t0); // right
	}


	return t;*/

	/*int mr = r1 + ((r2 - r1) / 2);
	int mc = c1 + ((c2 - c1) / 2);
	int t0 = 0;

	// 1.2
	/*if (r2 - r1 > c2 - c1) {
		t0 += findTreasure(map, n, r1, c1, mr, c2); // top
		t0 += findTreasure(map, n, mr + 1, c1, r2, c2, t - t0); // bottom
	} else {
		t0 += findTreasure(map, n, r1, c1, r2, mc); // left
		t0 += findTreasure(map, n, r1, mc + 1, r2, c2, t - t0); // right
	}*/

	// 1.99
	/*int tl = getNumberOfTreasuresInArea(map, r2, mc);
	if (tl == 0) {
		findTreasure(map, n, r1, c1, r2, mc, 0); // left
		findTreasure(map, n, r1, mc + 1, r2, c2, t); // right
	} else if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
		findTreasure(map, n, r1, c1, r2, mc, tl); // left
		findTreasure(map, n, r1, mc + 1, r2, c2, t - tl); // right
	} else {
		int tt = getNumberOfTreasuresInArea(map, mr, c2);
		if (tt == 0) {
			findTreasure(map, n, r1, c1, mr, c2, 0); // top
			findTreasure(map, n, mr + 1, c1, r2, c2, t); // bottom
		} else if (tt == (c2 - c1 + 1) * (mr - r1 + 1)) {
			findTreasure(map, n, r1, c1, mr, c2, tt); // top
			findTreasure(map, n, mr + 1, c1, r2, c2, t - tt); // bottom
		} else {
			if (r2 - r1 > c2 - c1) {
				findTreasure(map, n, r1, c1, mr, c2, tt); // top
				findTreasure(map, n, mr + 1, c1, r2, c2, t - tt); // bottom
			} else {
				findTreasure(map, n, r1, c1, r2, mc, tl); // left
				findTreasure(map, n, r1, mc + 1, r2, c2, t - tl); // right
			}
		}
	}

	return t;*/

	// 1.53
	/*int tl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, mc);
	int tt = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, c2), ttl;
	if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
		findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt - ((mr - r1 + 1) * (mc - c1 + 1))); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

		return t;
	} else if (tl == 0) {
		findTreasure(map, n, r1, c1, mr, mc, 0); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, 0); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tt); // 4

		return t;
	} else {
		t0 += findTreasure(map, n, r1, c1, mr, mc); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt -t0); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, tl - t0); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - t0))); // 4
		return t;
	}*/

	// 1.53
	/*int tl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, mc);
	int tt = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, c2), ttl;
	if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
		findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt - ((mr - r1 + 1) * (mc - c1 + 1))); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

		return t;
	} else if (tl == 0) {
		findTreasure(map, n, r1, c1, mr, mc, 0); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, 0); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tt); // 4

		return t;
	} else {
		ttl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, mc);

		findTreasure(map, n, r1, c1, mr, mc, ttl); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt - ttl); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, tl - ttl); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ttl))); // 4

		return t;
	}*/

	// 1.4
	/*int tl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, mc);
	int tt = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, c2), ttl;
	if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
		findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt - ((mr - r1 + 1) * (mc - c1 + 1))); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

		return t;
	} else if (tl == 0) {
		findTreasure(map, n, r1, c1, mr, mc, 0); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, 0); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tt); // 4

		return t;
	} else if (tt == (c2 - c1 + 1) * (mr - r1 + 1)) {
		findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, (mr - r1 + 1) * (c2 - (mc + 1) + 1)); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, tl - ((mr - r1 + 1) * (mc - c1 + 1))); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

		return t;
	} else if (tt == 0) {
		findTreasure(map, n, r1, c1, mr, mc, 0); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, 0); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, tl); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tl); // 4

		return t;
	} else {
		ttl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, mc);

		findTreasure(map, n, r1, c1, mr, mc, ttl); // 1
		findTreasure(map, n, r1, mc + 1, mr, c2, tt - ttl); // 2
		findTreasure(map, n, mr + 1, c1, r2, mc, tl - ttl); // 3
		findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ttl))); // 4

		return t;
	}*/

	// 1.26
	/*t0 += findTreasure(map, n, r1, c1, mr, mc); // 1

	if (t - t0 == ((r2 - (mr + 1) + 1) * (mc - c1 + 1)) + ((r2 - r1 + 1) * (c2 - (mc + 1) + 1))) {
		t0 += findTreasure(map, n, r1, mc + 1, mr, c2, (mr - r1 + 1) * (c2 - (mc + 1) + 1)); // 2
		t0 += findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
		t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, (r2 - (mr + 1) + 1) * (c2 - (mc + 1) + 1)); // 4
	} else {
		t0 += findTreasure(map, n, r1, mc + 1, mr, c2, t0 == t ? 0 : -1); // 2

		if (t - t0 == (r2 - (mr + 1) + 1) * (c2 - c1 + 1)) {
			t0 += findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
			t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, (r2 - (mr + 1) + 1) * (c2 - (mc + 1) + 1)); // 4
		} else {
			t0 += findTreasure(map, n, mr + 1, c1, r2, mc, t0 == t ? 0 : -1); // 3
			t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - t0); // 4
		}
	}*/

	// 1.4
	/*t0 += findTreasure(map, n, r1, c1, mr, mc);
	t0 += findTreasure(map, n, r1, mc + 1, mr, c2, t0 == t ? 0 : -1);
	t0 += findTreasure(map, n, mr + 1, c1, r2, mc, t0 == t ? 0 : -1);
	t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - t0);*/

	//return t0;
}

int getNumberOfTreasuresInArea(int **map, int r2, int c2) {
	int subcount = 0, ec = 0;
	for (int r = 0; r < r2; r++)
		for (int c = 0; c < c2; c++)
			if (map[r][c] == 1) subcount++;
			else if (map[r][c] == -1) ec++;

	if (ec > 1) {
		return -1;
	}

	//printf("Lookup [%d][%d]\n", r2, c2);
	int t = getNumberOfTreasuresInArea(1, 1, r2, c2);
	return t - subcount;
}

int getNumberOfTreasuresInAreaAfterMaximizing(int **map, const int N, int r1, int c1, int r2, int c2) {


	int subcount = 0;

	while (r1 > 1) {
		int count = 0;

		for (int i = c1 - 1; i < c2; i++) {
			if (map[r1 - 2][i] == 1) count++;
			else if (map[r1 - 2][i] == -1) {
				goto loop1;
			}
		}

		r1--;
		subcount += count;
	}
	loop1:

	while (r2 < N) {
		int count = 0;

		for (int i = c1 - 1; i < c2; i++) {
			if (map[r2][i] == 1) count++;
			else if (map[r2][i] == -1) {
				goto loop2;
			}
		}

		r2++;
		subcount += count;
	}
	loop2:

	while (c1 > 1) {
		int count = 0;

		for (int i = r1 - 1; i < r2; i++) {
			if (map[i][c1 - 2] == 1) count++;
			else if (map[i][c1 - 2] == -1) {
				goto loop3;
			}
		}

		c1--;
		subcount += count;
	}
	loop3:

	while (c2 < N) {
		int count = 0;

		for (int i = r1 - 1; i < r2; i++) {
			if (map[i][c2] == 1) count++;
			else if (map[i][c2] == -1) {
				goto loop4;
			}
		}

		c2++;
		subcount += count;
	}
	loop4:

	int count = getNumberOfTreasuresInArea(r1, c1, r2, c2);
	return count - subcount;
}

/*
 * #include "treasure.h"

#include <cstring>
#include <cmath>
#include <iostream>

int getNumberOfTreasuresInArea(int **map, int r2, int c2);
int findTreasure(int **map, int n, int r1, int c1, int r2, int c2, int treasure = -1);
int getNumberOfTreasuresInAreaAfterMaximizing(int **map, int N, int r1, int c1, int r2, int c2);

void findTreasure(int N) {

	auto map = (int **) calloc(N, sizeof(int *));
	for (int i = 0; i < N; i++) {
		map[i] = (int *) calloc(N, sizeof(int));
		memset(map[i], -1, N * sizeof(int));
	}

	findTreasure(map, N, 1, 1, N, N);

	for (int i = 0; i < N; i++)
		free(map[i]);
	free(map);
}

constexpr int l(const int a, const int b) {
	return a < b ? a : b;
}

constexpr int b(const int a, const int b) {
	return a > b ? a : b;
}

int findTreasure(int **map, const int n, const int r1, const int c1, const int r2, const int c2, const int treasure) {
	if (l(r1, r2) <= 0 || b(r1, r2) > n) return 0;
	if (l(c1, c2) <= 0 || b(c1, c2) > n) return 0;
	if (c1 > c2 || r1 > r2) return 0;

	//int t = treasure == -1 ? getNumberOfTreasuresInArea(map, r2, c2) : treasure;
	int t = treasure == -1 ? getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, c2) : treasure;
	//int t = getNumberOfTreasuresInArea(r1, c1, r2, c2);

	if (t == 0) {
		for (int r = r1; r <= r2; r++)
			for (int c = c1; c <= c2; c++)
				map[r - 1][c - 1] = 0;

		return 0;
	}

	if (t == (r2 - r1 + 1) * (c2 - c1 + 1)) {
		for (int r = r1; r <= r2; r++) {
			for (int c = c1; c <= c2; c++) {
				map[r - 1][c - 1] = 1;
				reportTreasure(r, c);
			}
		}

		return t;
	}


	int mc, mr, t0 = 0;

	/*if (n <= 4) {
		mr = r1 + ((r2 - r1) / 2);
		mc = c1 + ((c2 - c1) / 2);

		if (r2 - r1 > c2 - c1) {
			t0 += findTreasure(map, n, r1, c1, mr, c2); // top
			t0 += findTreasure(map, n, mr + 1, c1, r2, c2, t - t0); // bottom
		} else {
			t0 += findTreasure(map, n, r1, c1, r2, mc); // left
			t0 += findTreasure(map, n, r1, mc + 1, r2, c2, t - t0); // right
		}

		return t0;
	}

	/*{    // coll
		int rem = (c2 - c1 + 1) % 4;
		int a = floor(((double) (c2 - c1 + 1)) / 4);
		int b = 4;
		switch (rem) {
			case 1:
				b++;
				break;
			case 2:
				b++;
				a++;
				break;
			case 3:
				b += 2;
				a++;
			default:
				break;
		}
		mc = c1 + b;
	}

	{    // row
		int rem = (r2 - r1 + 1) % 4;
		int a = floor(((double) (r2 - r1 + 1)) / 4);
		int b = 4;
		switch (rem) {
			case 1:
				b++;
				break;
			case 2:
				b++;
				a++;
				break;
			case 3:
				b += 2;
				a++;
			default:
				break;
		}
		mr = r1 + b;
	}*/

/*mr = r2 - (int) ceil((double) (r2 - r1) / 2.5);
mc = c2 - (int) ceil((double) (c2 - c1) / 2.5);

/*if (r2 - r1 > c2 - c1) {
	t0 += findTreasure(map, n, mr + 1, c1, r2, c2); // bottom
	findTreasure(map, n, r1, c1, mr, c2, t - t0); // top
} else {
	t0 += findTreasure(map, n, r1, mc + 1, r2, c2); // right
	findTreasure(map, n, r1, c1, r2, mc, t - t0); // left
}*/

/*if (r2 - r1 > c2 - c1) {
t0 += findTreasure(map, n, r1, c1, mr, c2); // top
findTreasure(map, n, mr + 1, c1, r2, c2, t - t0); // bottom
} else {
t0 += findTreasure(map, n, r1, c1, r2, mc); // left
findTreasure(map, n, r1, mc + 1, r2, c2, t - t0); // right
}


return t;

/*int mr = r1 + ((r2 - r1) / 2);
int mc = c1 + ((c2 - c1) / 2);
int t0 = 0;

// 1.2
/*if (r2 - r1 > c2 - c1) {
	t0 += findTreasure(map, n, r1, c1, mr, c2); // top
	t0 += findTreasure(map, n, mr + 1, c1, r2, c2, t - t0); // bottom
} else {
	t0 += findTreasure(map, n, r1, c1, r2, mc); // left
	t0 += findTreasure(map, n, r1, mc + 1, r2, c2, t - t0); // right
}*/

// 1.99
/*int tl = getNumberOfTreasuresInArea(map, r2, mc);
if (tl == 0) {
	findTreasure(map, n, r1, c1, r2, mc, 0); // left
	findTreasure(map, n, r1, mc + 1, r2, c2, t); // right
} else if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
	findTreasure(map, n, r1, c1, r2, mc, tl); // left
	findTreasure(map, n, r1, mc + 1, r2, c2, t - tl); // right
} else {
	int tt = getNumberOfTreasuresInArea(map, mr, c2);
	if (tt == 0) {
		findTreasure(map, n, r1, c1, mr, c2, 0); // top
		findTreasure(map, n, mr + 1, c1, r2, c2, t); // bottom
	} else if (tt == (c2 - c1 + 1) * (mr - r1 + 1)) {
		findTreasure(map, n, r1, c1, mr, c2, tt); // top
		findTreasure(map, n, mr + 1, c1, r2, c2, t - tt); // bottom
	} else {
		if (r2 - r1 > c2 - c1) {
			findTreasure(map, n, r1, c1, mr, c2, tt); // top
			findTreasure(map, n, mr + 1, c1, r2, c2, t - tt); // bottom
		} else {
			findTreasure(map, n, r1, c1, r2, mc, tl); // left
			findTreasure(map, n, r1, mc + 1, r2, c2, t - tl); // right
		}
	}
}

return t;*/

// 1.53
/*int tl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, mc);
int tt = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, c2), ttl;
if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
	findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt - ((mr - r1 + 1) * (mc - c1 + 1))); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

	return t;
} else if (tl == 0) {
	findTreasure(map, n, r1, c1, mr, mc, 0); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, 0); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tt); // 4

	return t;
} else {
	t0 += findTreasure(map, n, r1, c1, mr, mc); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt -t0); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, tl - t0); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - t0))); // 4
	return t;
}*/

// 1.53
/*int tl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, mc);
int tt = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, c2), ttl;
if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
	findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt - ((mr - r1 + 1) * (mc - c1 + 1))); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

	return t;
} else if (tl == 0) {
	findTreasure(map, n, r1, c1, mr, mc, 0); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, 0); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tt); // 4

	return t;
} else {
	ttl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, mc);

	findTreasure(map, n, r1, c1, mr, mc, ttl); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt - ttl); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, tl - ttl); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ttl))); // 4

	return t;
}*/

// 1.4
/*int tl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, mc);
int tt = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, c2), ttl;
if (tl == (r2 - r1 + 1) * (mc - c1 + 1)) {
	findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt - ((mr - r1 + 1) * (mc - c1 + 1))); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

	return t;
} else if (tl == 0) {
	findTreasure(map, n, r1, c1, mr, mc, 0); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, 0); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tt); // 4

	return t;
} else if (tt == (c2 - c1 + 1) * (mr - r1 + 1)) {
	findTreasure(map, n, r1, c1, mr, mc, (mr - r1 + 1) * (mc - c1 + 1)); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, (mr - r1 + 1) * (c2 - (mc + 1) + 1)); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, tl - ((mr - r1 + 1) * (mc - c1 + 1))); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ((mr - r1 + 1) * (mc - c1 + 1))))); // 4

	return t;
} else if (tt == 0) {
	findTreasure(map, n, r1, c1, mr, mc, 0); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, 0); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, tl); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - tl); // 4

	return t;
} else {
	ttl = getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, mr, mc);

	findTreasure(map, n, r1, c1, mr, mc, ttl); // 1
	findTreasure(map, n, r1, mc + 1, mr, c2, tt - ttl); // 2
	findTreasure(map, n, mr + 1, c1, r2, mc, tl - ttl); // 3
	findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - (tl + (tt - ttl))); // 4

	return t;
}*/

// 1.26
/*t0 += findTreasure(map, n, r1, c1, mr, mc); // 1

if (t - t0 == ((r2 - (mr + 1) + 1) * (mc - c1 + 1)) + ((r2 - r1 + 1) * (c2 - (mc + 1) + 1))) {
	t0 += findTreasure(map, n, r1, mc + 1, mr, c2, (mr - r1 + 1) * (c2 - (mc + 1) + 1)); // 2
	t0 += findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
	t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, (r2 - (mr + 1) + 1) * (c2 - (mc + 1) + 1)); // 4
} else {
	t0 += findTreasure(map, n, r1, mc + 1, mr, c2, t0 == t ? 0 : -1); // 2

	if (t - t0 == (r2 - (mr + 1) + 1) * (c2 - c1 + 1)) {
		t0 += findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
		t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, (r2 - (mr + 1) + 1) * (c2 - (mc + 1) + 1)); // 4
	} else {
		t0 += findTreasure(map, n, mr + 1, c1, r2, mc, t0 == t ? 0 : -1); // 3
		t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - t0); // 4
	}
}*/

// 1.4
/*t0 += findTreasure(map, n, r1, c1, mr, mc);
t0 += findTreasure(map, n, r1, mc + 1, mr, c2, t0 == t ? 0 : -1);
t0 += findTreasure(map, n, mr + 1, c1, r2, mc, t0 == t ? 0 : -1);
t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - t0);*/

/*return t0;
}

int getNumberOfTreasuresInArea(int **map, int r2, int c2) {
	int subcount = 0;
	for (int r = 0; r < r2; r++)
		for (int c = 0; c < c2; c++)
			if (map[r][c] == 1) subcount++;

	//printf("Lookup [%d][%d]\n", r2, c2);
	int t = getNumberOfTreasuresInArea(1, 1, r2, c2);
	return t - subcount;
}

int getNumberOfTreasuresInAreaAfterMaximizing(int **map, const int N, int r1, int c1, int r2, int c2) {


	int subcount = 0;

	while (r1 > 1) {
		int count = 0;

		for (int i = c1 - 1; i < c2; i++) {
			if (map[r1 - 2][i] == 1) count++;
			else if (map[r1 - 2][i] == -1) {
				goto loop1;
			}
		}

		r1--;
		subcount += count;
	}
	loop1:

	while (r2 < N) {
		int count = 0;

		for (int i = c1 - 1; i < c2; i++) {
			if (map[r2][i] == 1) count++;
			else if (map[r2][i] == -1) {
				goto loop2;
			}
		}

		r2++;
		subcount += count;
	}
	loop2:

	while (c1 > 1) {
		int count = 0;

		for (int i = r1 - 1; i < r2; i++) {
			if (map[i][c1 - 2] == 1) count++;
			else if (map[i][c1 - 2] == -1) {
				goto loop3;
			}
		}

		c1--;
		subcount += count;
	}
	loop3:

	while (c2 < N) {
		int count = 0;

		for (int i = r1 - 1; i < r2; i++) {
			if (map[i][c2] == 1) count++;
			else if (map[i][c2] == -1) {
				goto loop4;
			}
		}

		c2++;
		subcount += count;
	}
	loop4:

	int count = getNumberOfTreasuresInArea(r1, c1, r2, c2);
	return count - subcount;
}
 * */

/**
 *
 * #include "treasure.h"

#include <cstring>
#include <iostream>

int getNumberOfTreasuresInArea(int **map, int r2, int c2);
int findTreasure(int **map, int n, int r1, int c1, int r2, int c2, int treasure = -1);

void findTreasure(int N) {

	auto map = (int **) calloc(N, sizeof(int *));
	for (int i = 0; i < N; i++) {
		map[i] = (int *) calloc(N, sizeof(int));
		memset(map[i], -1, N * sizeof(int));
	}

	findTreasure(map, N, 1, 1, N, N);

	for (int i = 0; i < N; i++)
		free(map[i]);
	free(map);
}

constexpr int l(const int a, const int b) {
	return a < b ? a : b;
}

constexpr int b(const int a, const int b) {
	return a > b ? a : b;
}

int findTreasure(int **map, const int n, const int r1, const int c1, const int r2, const int c2, const int treasure) {
	if (l(r1, r2) <= 0 || b(r1, r2) > n) return 0;
	if (l(c1, c2) <= 0 || b(c1, c2) > n) return 0;
	if (c1 > c2 || r1 > r2) return 0;

	int t = treasure == -1 ? getNumberOfTreasuresInArea(map, r2, c2) : treasure;

	if (t == 0) {
		for (int r = r1; r <= r2; r++)
			for (int c = c1; c <= c2; c++)
				map[r - 1][c - 1] = 0;

		return 0;
	}

	if (t == (r2 - r1 + 1) * (c2 - c1 + 1)) {
		for (int r = r1; r <= r2; r++) {
			for (int c = c1; c <= c2; c++) {
				map[r - 1][c - 1] = 1;
				reportTreasure(r, c);
			}
		}

		return t;
	}

	int mr = r1 + ((r2 - r1) / 2);
	int mc = c1 + ((c2 - c1) / 2);

	int t0 = 0;
	t0 += findTreasure(map, n, r1, c1, mr, mc);
	t0 += findTreasure(map, n, r1, mc + 1, mr, c2, t0 == t ? 0 : -1);
	t0 += findTreasure(map, n, mr + 1, c1, r2, mc, t0 == t ? 0 : -1);
	t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - t0);

	return t0;
}

int getNumberOfTreasuresInArea(int **map, int r2, int c2) {
	int subcount = 0;
	for (int r = 0; r < r2; r++)
		for (int c = 0; c < c2; c++)
			if (map[r][c] == 1) subcount++;

	int t = getNumberOfTreasuresInArea(1, 1, r2, c2);
	return t - subcount;
}*/

/*
 *#include "treasure.h"

#include <cstring>
#include <cmath>
#include <iostream>

int getNumberOfTreasuresInArea(int **map, int r2, int c2);
int findTreasure(int **map, int n, int r1, int c1, int r2, int c2, int treasure = -1);
int getNumberOfTreasuresInAreaAfterMaximizing(int **map, int N, int r1, int c1, int r2, int c2);

void findTreasure(int N) {

	auto map = (int **) calloc(N, sizeof(int *));
	for (int i = 0; i < N; i++) {
		map[i] = (int *) calloc(N, sizeof(int));
		memset(map[i], -1, N * sizeof(int));
	}

	findTreasure(map, N, 1, 1, N, N);

	for (int i = 0; i < N; i++)
		free(map[i]);
	free(map);
}

constexpr int l(const int a, const int b) {
	return a < b ? a : b;
}

constexpr int b(const int a, const int b) {
	return a > b ? a : b;
}

int findTreasure(int **map, const int n, const int r1, const int c1, const int r2, const int c2, const int treasure) {
	if (l(r1, r2) <= 0 || b(r1, r2) > n) return 0;
	if (l(c1, c2) <= 0 || b(c1, c2) > n) return 0;
	if (c1 > c2 || r1 > r2) return 0;

	int t = treasure == -1 ? getNumberOfTreasuresInArea(map, r2, c2) : treasure;
	// int t = treasure == -1 ? getNumberOfTreasuresInAreaAfterMaximizing(map, n, r1, c1, r2, c2) : treasure;
	// int t = getNumberOfTreasuresInArea(r1, c1, r2, c2);

	if (t == 0) {
		for (int r = r1; r <= r2; r++)
			for (int c = c1; c <= c2; c++)
				map[r - 1][c - 1] = 0;

		return 0;
	}

	if (t == (r2 - r1 + 1) * (c2 - c1 + 1)) {
		for (int r = r1; r <= r2; r++) {
			for (int c = c1; c <= c2; c++) {
				map[r - 1][c - 1] = 1;
				reportTreasure(r, c);
			}
		}

		return t;
	}

	int mr = r1 + ((r2 - r1) / 2);
	int mc = c1 + ((c2 - c1) / 2);

	/*int t0 = 0;
	if (r2 - r1 > c2 - c1) {
		t0 += findTreasure(map, n, r1, c1, mr, c2);
		t0 += findTreasure(map, n, mr + 1, c1, r2, c2, t - t0);
	} else {
		t0 += findTreasure(map, n, r1, c1, r2, mc);
		t0 += findTreasure(map, n, r1, mc + 1, r2, c2, t - t0);
	} * /

int t0 = 0;
t0 += findTreasure(map, n, r1, c1, mr, mc); // 1

if (t - t0 == ((r2 - (mr + 1) + 1) * (mc - c1 + 1)) + ((r2 - r1 + 1) * (c2 - (mc + 1) + 1))) {
t0 += findTreasure(map, n, r1, mc + 1, mr, c2, (mr - r1 + 1) * (c2 - (mc + 1) + 1)); // 2
t0 += findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, (r2 - (mr + 1) + 1) * (c2 - (mc + 1) + 1)); // 4
} else {
t0 += findTreasure(map, n, r1, mc + 1, mr, c2, t0 == t ? 0 : -1); // 2

if (t - t0 == (r2 - (mr + 1) + 1) * (c2 - c1 + 1)) {
t0 += findTreasure(map, n, mr + 1, c1, r2, mc, (r2 - (mr + 1) + 1) * (mc - c1 + 1)); // 3
t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, (r2 - (mr + 1) + 1) * (c2 - (mc + 1) + 1)); // 4
} else {
t0 += findTreasure(map, n, mr + 1, c1, r2, mc, t0 == t ? 0 : -1); // 3
t0 += findTreasure(map, n, mr + 1, mc + 1, r2, c2, t - t0); // 4
}
}

return t0;
}

int getNumberOfTreasuresInArea(int **map, int r2, int c2) {
	int subcount = 0;
	for (int r = 0; r < r2; r++)
		for (int c = 0; c < c2; c++)
			if (map[r][c] == 1) subcount++;

	//printf("Lookup [%d][%d]\n", r2, c2);
	int t = getNumberOfTreasuresInArea(1, 1, r2, c2);
	return t - subcount;
}
 * */