#include "fse.h"

using namespace std;

int rows, cols;

bool isThereSmth(vector<string> *lines, int ref_y, int ref_x, char c) {
	if (ref_y >= rows || ref_y < 0 || ref_x >= cols || ref_x < 0) return false;

	switch (c) {
		case 'v':
			for (int y = ref_y; y < rows; y++) {
				if ((*lines)[y][ref_x] != '.') {
					return true;
				}
			}
			return false;
		case '^':
			for (int y = ref_y; y > 0; y--) {
				if ((*lines)[y][ref_x] != '.') {
					return true;
				}
			}
			return false;
		case '>':
			for (int x = ref_x; x < cols; x++) {
				if ((*lines)[ref_y][x] != '.') {
					return true;
				}
			}
			return false;
		case '<':
			for (int x = ref_x; x > 0; x--) {
				if ((*lines)[ref_y][x] != '.') {
					return true;
				}
			}
			return false;
		default:
			return false;
	}
}

int resolve(vector<string> *lines, char c, int ref) {
	switch (c) {
		case '^': {
			int y = 0;
			for (; y < rows && (*lines)[y][ref] == '.'; y++) {}
			if (y == rows) return 0;
			else {
				if ((*lines)[y][ref] == '^') {
					if (isThereSmth(lines, y + 1, ref, 'v') ||
						isThereSmth(lines, y, ref - 1, '<') ||
						isThereSmth(lines, y, ref + 1, '>')) {
						return 1;
					} else return -1;
				} else return 0;
			}
		}
		case 'v': {
			int y = rows - 1;
			for (; y > 0 && (*lines)[y][ref] == '.'; y--) {}
			if (y == 0) return 0;
			else {
				if ((*lines)[y][ref] == 'v') {
					if (isThereSmth(lines, y - 1, ref, '^') ||
						isThereSmth(lines, y, ref - 1, '<') ||
						isThereSmth(lines, y, ref + 1, '>')) {
						return 1;
					} else return -1;
				} else return 0;
			}
		}
		case '<': {
			int x = 0;
			for (; x < cols && (*lines)[ref][x] == '.'; x++) {}
			if (x == cols) return 0;
			else {
				if ((*lines)[ref][x] == '<') {
					if (isThereSmth(lines, ref - 1, x, '^') ||
						isThereSmth(lines, ref + 1, x, 'v') ||
						isThereSmth(lines, ref, x + 1, '>')) {
						return 1;
					} else return -1;
				} else return 0;
			}
		}
		case '>': {
			int x = cols - 1;
			for (; x > 0 && (*lines)[ref][x] == '.'; x--) {}
			if (x == 0) return 0;
			else {
				if ((*lines)[ref][x] == '>') {
					if (isThereSmth(lines, ref - 1, x, '^') ||
						isThereSmth(lines, ref + 1, x, 'v') ||
						isThereSmth(lines, ref, x - 1, '<')) {
						return 1;
					} else return -1;
				} else return 0;
			}
		}
		default:
			return -1;
	}
}

int solve(vector<string> lines) {
	rows = lines.size(); // n
	cols = lines[0].size(); // m

	int amt = 0;

	for (int x = 0; x < cols; x++) {
		if (lines[0][x] == '^') amt++;
		else if (lines[0][x] == '.') {
			int r = resolve(&lines, '^', x);
			if (r >= 1) amt++;
			else if (r == -1) return -1;
		}

		if (lines[rows - 1][x] == 'v') amt++;
		else if (lines[rows - 1][x] == '.') {
			int r = resolve(&lines, 'v', x);
			if (r >= 1) amt++;
			else if (r == -1) return -1;
		}
	}

	for (int y = 0; y < rows; y++) {
		if (lines[y][0] == '<') amt++;
		else if (lines[y][0] == '.') {
			int r = resolve(&lines, '<', y);
			if (r >= 1) amt++;
			else if (r == -1) return -1;
		}

		if (lines[y][cols - 1] == '>') amt++;
		else if (lines[y][cols - 1] == '.') {
			int r = resolve(&lines, '>', y);
			if (r >= 1) amt++;
			else if (r == -1) return -1;
		}
	}

	int c = 0;
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			if (lines[y][x] != '.') c++;
			if (c > 1) return amt;
		}
	}
	return -1;
}