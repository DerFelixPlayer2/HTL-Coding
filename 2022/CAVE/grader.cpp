//Der Grader online kann von diesem Beispielgrader abweichen!
#include <cstdio>
#include <cstdlib>
#include "cave.h"
#include <fstream>
#include <iostream>


static const int MAX_N = 1005;

static int r, c, steps, max_steps;
static char grid[MAX_N][MAX_N], fieldOfView[3][3];

static void makeFieldOfView() {
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			fieldOfView[1 + i][1 + j] = grid[r + i][c + j];
}

static void move(int dx, int dy) {
	steps++;
	//std::cout << steps << std::endl;
	if (steps > max_steps) {
		//std::cout << steps << std::endl;
		printf("Zu viele Schritte\n");
		exit(0);
	}
	char here = grid[r + dy][c + dx];
	if (here == '#') {
		//std::cout << steps << std::endl;
		return;
	}
	if (here == 'X') {
		//std::cout << steps << std::endl;
		printf("Richtig, %d Schritte\n", steps);
		exit(0);
	}
	grid[r][c] = '.';
	grid[r + dy][c + dx] = 'S';
	r += dy, c += dx;
	makeFieldOfView();
}

void left() { move(-1, 0); }

void right() { move(1, 0); }

void up() { move(0, -1); }

void down() { move(0, 1); }

int main() {
	int s, n, m;

	FILE *file = fopen("../cave4.txt", "r");

	if (file == nullptr) return -1;

	fscanf(file, "%d %d %d", &s, &n, &m);
	max_steps = 2000000;
	for (int i = 0; i < n; i++) {
		fscanf(file, "%s", grid[i]);
		for (int j = 0; j < m; j++)
			if (grid[i][j] == 'S')
				r = i, c = j;
	}
	makeFieldOfView();
	findExit(s, fieldOfView);
	printf("Ausgang nicht gefunden\n");
	return 0;
}
