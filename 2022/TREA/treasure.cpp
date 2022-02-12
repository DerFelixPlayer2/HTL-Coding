#include "treasure.h"

#include <iostream>
#include <cstring>
#include <random>

void findTreasure(short **map, int N, int r1, int c1, int r2, int c2);
int getNumberOfTreasuresInArea(short **map, int N, int r1, int c1, int r2, int c2);

void findTreasure(int N) {
	auto **map = (short **) calloc(N, sizeof(short *));
	for (int i = 0; i < N; i++) {
		map[i] = (short *) calloc(N, sizeof(short));
		memset(map[i], -1, N * sizeof(short));
	}


	findTreasure(map, N, 1, 1, N, N);

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++)
			printf("%d ", map[r - 1][c - 1]);
		printf("\n");
	}
}

void findTreasure(short **map, int N, int r1, int c1, int r2, int c2) {
	if (std::min(r1, c1) <= 0 || std::max(r2, c2) > N) return;
	if (std::min(r2, c2) <= 0 || std::max(r1, c1) > N) return;

	/*for (int i = r1 - 1; i < r2; i++)
		for (int j = c1 - 1; j < c2; j++)
			if (map[i][j] == -1)
				goto resume;
	return;

	resume:*/

	int treasure = getNumberOfTreasuresInArea(map, N, r1, c1, r2, c2);

	if (treasure == (r2 - r1 + 1) * (c2 - c1 + 1)) {
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				reportTreasure(i, j);
				map[i - 1][j - 1] = 1;
			}
		}

		return;
	}

	if (treasure == 0) {
		for (int i = r1 - 1; i < r2; i++) {
			for (int j = c1 - 1; j < c2; j++) {
				map[i][j] = 0;
			}
		}

		return;
	}

	if (r1 == r2 && c1 == c2) {
		reportTreasure(r1, c1);
		map[r1 - 1][c1 - 1] = 1;
		return;
	}


	printf("N: %d, trea: %d, 1: %d %d, 2: %d %d\n", N, treasure, r1, c1, r2, c2);

	int mr = r1 + ((r2 - r1) / 2);
	int mc = c1 + ((c2 - c1) / 2);

	int ar1 = r1;
	int ac1 = c1;
	int ar2 = mr;
	int ac2 = mc;

	int br1 = ar1;
	int bc1 = ac2 + 1;
	int br2 = ar2;
	int bc2 = c2;

	int cr1 = ar2 + 1;
	int cc1 = ac1;
	int cr2 = r2;
	int cc2 = ac2;

	int dr1 = cr1;
	int dc1 = bc1;
	int dr2 = r2;
	int dc2 = c2;

	findTreasure(map, N, ar1, ac1, ar2, ac2);
	findTreasure(map, N, br1, bc1, br2, bc2);
	findTreasure(map, N, cr1, cc1, cr2, cc2);
	findTreasure(map, N, dr1, dc1, dr2, dc2);
}

int getNumberOfTreasuresInArea(short **map, int N, int r1, int c1, int r2, int c2) {
	return getNumberOfTreasuresInArea(r1, c1, r2, c2);

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

	printf("%d - %d\n", count, subcount);

	return count - subcount;
}