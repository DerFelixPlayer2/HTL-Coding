#include "cave.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

enum DIR {
	RIGHT, UP, LEFT, DOWN, null
};

struct Stack {
	DIR *data;
	int size;
	int top;

	explicit Stack(int size) {
		this->data = (DIR *) malloc(size * sizeof(DIR));
		this->size = size;
		this->top = 0;
	}

	void push(DIR dir) {
		if (this->top < this->size) {
			this->data[this->top++] = dir;
		} else {
			size *= 2;
			this->data = (DIR *) realloc(this->data, size * sizeof(DIR));
			if (this->data == nullptr)
				exit(-2);
			push(dir);
		}
	}

	DIR pop() {
		if (this->top > 0) return this->data[--this->top];
		exit(-1);
	}
};

struct Node {
	int x, y;
	int parentX, parentY;
	float gCost, hCost, fCost;
};

size_t height = 10;
size_t width = height;
Stack *stack = new Stack(10);
int xx = -1, xy = -1;

/*inline bool operator<(const Node &lhs, const Node &rhs) {
	return lhs.fCost < rhs.fCost;
}

class astar {
	char **map;

	static bool isValid(int x, int y) {
		return map[y][x] != '#';
	}

	static bool isDestination(int x, int y, Node dest) {
		return x == dest.x && y == dest.y;
	}

	static double calculateH(int x, int y, Node dest) {
		return sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y));
	}

	static vector<Node> aStar(Node player, Node dest) {
		vector<Node> empty;
		bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

		//Initialize whole map
		//Node allMap[50][25];
		array<array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
		for (int x = 0; x < (X_MAX / X_STEP); x++) {
			for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
				allMap[x][y].fCost = FLT_MAX;
				allMap[x][y].gCost = FLT_MAX;
				allMap[x][y].hCost = FLT_MAX;
				allMap[x][y].parentX = -1;
				allMap[x][y].parentY = -1;
				allMap[x][y].x = x;
				allMap[x][y].y = y;

				closedList[x][y] = false;
			}
		}

		//Initialize our starting list
		int x = player.x;
		int y = player.y;
		allMap[x][y].fCost = 0.0;
		allMap[x][y].gCost = 0.0;
		allMap[x][y].hCost = 0.0;
		allMap[x][y].parentX = x;
		allMap[x][y].parentY = y;

		vector<Node> openList;
		openList.emplace_back(allMap[x][y]);
		bool destinationFound = false;

		while (!openList.empty()&&openList.size()<(X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
			Node node;
			do {
				//This do-while loop could be replaced with extracting the first
				//element from a set, but you'd have to make the openList a set.
				//To be completely honest, I don't remember the reason why I do
				//it with a vector, but for now it's still an option, although
				//not as good as a set performance wise.
				float temp = FLT_MAX;
				vector<Node>::iterator itNode;
				for (vector<Node>::iterator it = openList.begin();
					 it != openList.end(); it = next(it)) {
					Node n = *it;
					if (n.fCost < temp) {
						temp = n.fCost;
						itNode = it;
					}
				}
				node = *itNode;
				openList.erase(itNode);
			} while (isValid(node.x, node.y) == false);

			x = node.x;
			y = node.y;
			closedList[x][y] = true;

			//For each neighbour starting from North-West to South-East
			for (int newX = -1; newX <= 1; newX++) {
				for (int newY = -1; newY <= 1; newY++) {
					double gNew, hNew, fNew;
					if (isValid(x + newX, y + newY)) {
						if (isDestination(x + newX, y + newY, dest))
						{
							//Destination found - make path
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							destinationFound = true;
							return makePath(allMap, dest);
						}
						else if (closedList[x + newX][y + newY] == false)
						{
							gNew = node.gCost + 1.0;
							hNew = calculateH(x + newX, y + newY, dest);
							fNew = gNew + hNew;
							// Check if this path is better than the one already present
							if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
								allMap[x + newX][y + newY].fCost > fNew)
							{
								// Update the details of this neighbour node
								allMap[x + newX][y + newY].fCost = fNew;
								allMap[x + newX][y + newY].gCost = gNew;
								allMap[x + newX][y + newY].hCost = hNew;
								allMap[x + newX][y + newY].parentX = x;
								allMap[x + newX][y + newY].parentY = y;
								openList.emplace_back(allMap[x + newX][y + newY]);
							}
						}
					}
				}
			}
		}
		if (destinationFound == false) {
			cout << "Destination not found" << endl;
			return empty;
		}
	}

	static vector<Node> makePath(array<array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
		try {
			cout << "Found a path" << endl;
			int x = dest.x;
			int y = dest.y;
			stack<Node> path;
			vector<Node> usablePath;

			while (!(map[x][y].parentX == x && map[x][y].parentY == y)
				   && map[x][y].x != -1 && map[x][y].y != -1)
			{
				path.push(map[x][y]);
				int tempX = map[x][y].parentX;
				int tempY = map[x][y].parentY;
				x = tempX;
				y = tempY;

			}
			path.push(map[x][y]);

			while (!path.empty()) {
				Node top = path.top();
				path.pop();
				usablePath.emplace_back(top);
			}
			return usablePath;
		}
		catch(const exception& e){
			cout << e.what() << endl;
		}
	}


};*/

void gotoExitIfInSight(char fieldOfView[3][3], int x, int y) {
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++)
			if (fieldOfView[i][j] == 'X') {
				if (i == 1 || j == 1) {
					if (i == 0) up();
					else if (i == 2) down();
					else if (j == 0) left();
					else right();
				} else {
					if (i == j) {
						if (i == 0) {
							xx = x - 1;
							xy = y - 1;

							if (fieldOfView[0][1] == '#') {
								left();
								up();
							} else {
								up();
								left();
							}
						} else {
							xx = x + 1;
							xy = y + 1;

							if (fieldOfView[2][1] == '#') {
								right();
								down();
							} else {
								down();
								right();
							}
						}
					} else {
						if (i == 0) {
							xx = x + 1;
							xy = y - 1;

							if (fieldOfView[0][1] == '#') {
								right();
								up();
							} else {
								up();
								right();
							}
						} else {
							xx = x - 1;
							xy = y - 1;

							if (fieldOfView[2][1] == '#') {
								left();
								down();
							} else {
								down();
								left();
							}
						}
					}
				}
			}
}

char **shiftDown(char **map) {
	if (strlen(map[height - 1]) > 0) {
		map = (char **) realloc(map, (++height) * sizeof(char *));
		if (map == nullptr)
			exit(-2);
		map[height - 1] = (char *) calloc(width, sizeof(char));
	}

	auto last = map[height - 1];
	for (size_t i = height - 1; i > 0; i--)
		map[i] = map[i - 1];
	map[0] = last;
	memset(map[0], 0, width * sizeof(char));
	return map;
}

char **shiftRight(char **map) {
	for (int i = 0; i < height; i++) {
		if (map[i][width - 1] != 0) {
			width *= 2;

			for (i = 0; i < height; i++) {
				map[i] = (char *) realloc(map[i], width * sizeof(char));
				if (map[i] == nullptr)
					exit(-2);
				for (size_t j = width / 2; j < width; j++)
					map[i][j] = 0;
			}

			break;
		}
	}

	for (auto j = 0; j < height; j++) {
		for (size_t i = width - 1; i > 0; i--)
			map[j][i] = map[j][i - 1];
		map[j][0] = 0;
	}
	return map;
}

bool hasUndiscoveredNeighbours(char **map, int xx, int yy) {
	for (int y = yy - 1; y <= yy + 1; y++) {
		for (int x = xx - 1; x <= xx + 1; x++) {
			if (y < 0 || y > height - 1 || x < 0 || x > width - 1 || map[y][x] == 0)
				return true;
		}
	}

	return false;
}

DIR findPathTo(char **map, int x, int y, int dest_x, int dest_y) {

	if (dest_x > x) {
		if (map[y][x + 1] != '#') return RIGHT;
	}

	if (dest_x < x) {
		if (map[y][x - 1] != '#') return LEFT;
	}

	if (dest_y > y) {
		if (map[y + 1][x] != '#') return DOWN;
	}

	if (dest_y < y) {
		if (map[y - 1][x] != '#') return UP;
	}

	if (map[y][x + 1] != '#') return RIGHT;
	if (map[y][x - 1] != '#') return LEFT;
	if (map[y + 1][x] != '#') return DOWN;
	return UP;
}

DIR opposite(DIR dir) {
	switch (dir) {
		case RIGHT:
			return LEFT;
		case UP:
			return DOWN;
		case LEFT:
			return RIGHT;
		case DOWN:
			return UP;
		default:
			return null;
	}
}

void move(DIR dir) {
	switch (dir) {
		case RIGHT:
			right();
			break;
		case UP:
			up();
			break;
		case LEFT:
			left();
			break;
		case DOWN:
			down();
		default:
			break;
	}
}

/*void goToExitIfFound(char **map, int from_x, int from_y, int to_x, int to_y) {
	DIR *way = astar(map, from_x, from_y, to_x, to_y);

	if (way == nullptr) {
		return;
	}

	for (int i = 0; way[i] != null; i++) {
		move(way[i]);
	}

	free(way);

}*/

DIR calculateNextDirection(char fieldOfView[3][3], char **map, int x, int y) {
	/*if (xx != -1 && xy != -1) {
		goToExitIfFound(map, x, y, xx, xy);
		return null;
	}*/

	for (int i = 0; i <= 2; i++) {
		if (i == 1) continue;
		for (int j = 0; j <= 2; j++) {
			if (fieldOfView[i][j] != '#') {
				if (hasUndiscoveredNeighbours(map, x + (j - 1), y + (i - 1))) {
					DIR d = findPathTo(map, x, y, x + (j - 1), y + (i - 1));
					stack->push(d);
					return d;
				}
			}
		}
	}

	for (int i = 0; i <= 2; i++) {
		if (i == 1) continue;
		for (int j = 0; j <= 2; j++) {
			if (fieldOfView[j][i] != '#') {
				if (hasUndiscoveredNeighbours(map, x + (i - 1), y + (j - 1))) {
					DIR d = findPathTo(map, x, y, x + (i - 1), y + (j - 1));
					stack->push(d);
					return d;
				}
			}
		}
	}

	return opposite(stack->pop());
}

void findExit(int subtask, char fieldOfView[3][3]) {

	std::ios_base::sync_with_stdio(false);

	/*switch (subtask) {
		case 1:

			while (true) {
				gotoExitIfInSight(fieldOfView);

				if (fieldOfView[1][0] == '#') {
					if (fieldOfView[2][1] == '#') right();
					else down();
				} else if (fieldOfView[0][1] == '#') {
					if (fieldOfView[1][0] == '#') down();
					else left();
				} else if (fieldOfView[2][1] == '#') {
					if (fieldOfView[1][2] == '#') up();
					else right();
				} else {
					up();
				}

				if (fieldOfView[1][1] == '.') return;
			}

		case 2:
			while (fieldOfView[1][0] != '#')
				left();

			while (fieldOfView[2][1] != '#')
				down();

			while (true) {
				while (fieldOfView[0][1] != '#') {
					gotoExitIfInSight(fieldOfView);
					up();
				}

				right();
				right();
				right();

				while (fieldOfView[2][1] != '#') {
					gotoExitIfInSight(fieldOfView);
					down();
				}

				right();
				right();
				right();

				if (fieldOfView[1][1] == '.') return;
			}

		case 3:

			while (true) {
				/*for (int i = 0; i <= 2; i++) {
					for (int j = 0; j <= 2; j++)
						std::cout << fieldOfView[i][j];
					std::cout << std::endl;
				}
				std::cout << std::endl;


				// TODO: double border (no corner)
				gotoExitIfInSight(fieldOfView);

				switch (dir) {
					case RIGHT:
						if (fieldOfView[2][1] == '#' && fieldOfView[2][2] != '#') {
							dir = DOWN;
						} else if (fieldOfView[1][2] == '#') {
							dir = UP;
							break;
						}
						right();
						break;
					case UP:
						if (fieldOfView[1][2] == '#' && fieldOfView[0][2] != '#') {
							dir = RIGHT;
						} else if (fieldOfView[0][1] == '#') {
							dir = LEFT;
							break;
						}
						up();
						break;
					case LEFT:
						if (fieldOfView[0][1] == '#' && fieldOfView[0][0] != '#') {
							dir = UP;
						} else if (fieldOfView[1][0] == '#') {
							dir = DOWN;
							break;
						}
						left();
						break;
					case DOWN:
						if (fieldOfView[1][0] == '#' && fieldOfView[2][0] != '#') {
							dir = LEFT;
						} else if (fieldOfView[2][1] == '#') {
							dir = RIGHT;
							break;
						}
						down();
						break;
				}

				if (fieldOfView[1][1] == '.') return;
			}


		case 4:
		case 5:
		default:
			break;
	}*/

	DIR dir;
	int i = 0, j = 0;
	auto map = (char **) calloc(height, sizeof(char *));
	for (int k = 0; k < height; k++)
		map[k] = (char *) calloc(width, sizeof(char));

	while (true) {
		//gotoExitIfInSight(fieldOfView, j + 1, i + 1);
		gotoExitIfInSight(fieldOfView, -1, -1);

		for (int m = 0; m <= 2; m++) {
			for (int n = 0; n <= 2; n++) {
				map[m + i][n + j] = fieldOfView[m][n];
			}
		}

		/*for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++)
				std::cout << fieldOfView[i][j];
			std::cout << std::endl;
		}
		std::cout << "+++++++++++++" << std::endl;*/

		/*{
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++)
					std::cout << map[i][j];
				std::cout << std::endl;
			}
			std::cout << "---------" << std::endl;
		}*/

		{
			int y = i + 1;
			int x = j + 1;

			dir = calculateNextDirection(fieldOfView, map, x, y);
			//std::cout << dir << std::endl;
			// std::cout << width << " " << height << std::endl;
		}

		switch (dir) {
			case RIGHT:
				right();
				break;
			case UP:
				up();
				break;
			case LEFT:
				left();
				break;
			case DOWN:
				down();
				break;
			default:
				delete stack;
				exit(1);
		}

		switch (dir) {
			case RIGHT:
				j++;

				if (j + 2 >= width) {
					width *= 2;

					for (size_t k = 0; k < height; k++) {
						map[k] = (char *) realloc(map[k], sizeof(char) * width);
						if (map[k] == nullptr)
							exit(-2);
						for (size_t i = width / 2; i < width; i++)
							map[k][i] = 0;
					}
				}

				break;
			case UP:

				if (i == 0) {
					map = shiftDown(map);
					if (xy != -1) xy++;
				} else {
					i--;
				}

				break;
			case LEFT:

				if (j == 0) {
					map = shiftRight(map);
					if (xx != -1) xx++;
				} else {
					j--;
				}

				break;
			case DOWN:
				i++;

				if (i + 2 >= height) {
					height *= 2;
					map = (char **) realloc(map, sizeof(char *) * height);

					if (map == nullptr)
						exit(-2);

					for (size_t i = (height / 2) - 1; i < height; i++)
						map[i] = (char *) malloc(sizeof(char) * width);
				}

			default:
				break;

		}

		if (fieldOfView[1][1] == '.') {
			delete stack;
			exit(2);
		}

	}

}