#include "cave.h"
#include <cstring>
#include <iostream>
#include <stack>

#define NOT_FOUND -3
#define MEMORY_ERROR -2
#define INVALID_STATE -1
static int const default_size = 10;

enum class Direction {
	RIGHT, UP, LEFT, DOWN, null
};

class Map {
	char **map;
	int relative_pos_x, relative_pos_y;
	int height, width;

public:
	Map() {
		this->relative_pos_x = 1;
		this->relative_pos_y = 1;
		this->height = default_size;
		this->width = default_size;

		this->map = (char **) calloc(height, sizeof(char *));
		for (int i = 0; i < height; i++) {
			this->map[i] = (char *) calloc(width, sizeof(char));
			memset(this->map[i], 0, sizeof(char) * width);
		}
	}

	explicit Map(char fieldOfView[3][3]) : Map() {
		for (int y = -1; y <= 1; y++) {
			for (int x = -1; x <= 1; x++) {
				this->map[y + relative_pos_y][x + relative_pos_x] = fieldOfView[y + relative_pos_y][x + relative_pos_x];
			}
		}
	}

	virtual ~Map() {
		for (int i = 0; i < height; i++)
			free(this->map[i]);
		free(this->map);
	}

	void set(int rel_y, int reL_x, char symb) const {
		this->map[relative_pos_y + rel_y][relative_pos_x + reL_x] = symb;
	}

	void update(Direction direction, char fieldOfView[3][3]) {
		switch (direction) {
			case Direction::RIGHT:
				relative_pos_x++;

				if (relative_pos_x + 1 >= width) {
					width *= 2;

					for (size_t k = 0; k < height; k++) {
						map[k] = (char *) realloc(map[k], sizeof(char) * width);
						if (map[k] == nullptr)
							exit(MEMORY_ERROR);

						for (size_t i = width / 2; i < width; i++)
							map[k][i] = 0;
					}
				}

				break;
			case Direction::UP:
				relative_pos_y--;

				if (relative_pos_y == 0) {
					shiftDown();
					relative_pos_y++;
				}

				break;
			case Direction::LEFT:
				relative_pos_x--;

				if (relative_pos_x == 0) {
					shiftRight();
					relative_pos_x++;
				}

				break;
			case Direction::DOWN:
				relative_pos_y++;

				if (relative_pos_y + 1 >= height) {
					height *= 2;
					map = (char **) realloc(map, sizeof(char *) * height);

					if (map == nullptr)
						exit(MEMORY_ERROR);

					for (size_t i = (height / 2) - 1; i < height; i++) {
						map[i] = (char *) calloc(width, sizeof(char));
						if (map[i] == nullptr)
							exit(MEMORY_ERROR);

						memset(map[i], 0, sizeof(char) * width);
					}
				}

				break;
			default:
				exit(INVALID_STATE);
		}

		for (int y = -1; y <= 1; y++) {
			for (int x = -1; x <= 1; x++) {
				map[y + relative_pos_y][x + relative_pos_x] = fieldOfView[y + 1][x + 1];
			}
		}
	}

	[[nodiscard]] Direction hasUndiscoveredNeighbors() const {
		for (int y = relative_pos_y - 2; y <= relative_pos_y + 2; y++) {
			for (int x = relative_pos_x - 2; x <= relative_pos_x + 2; x++) {
				if (x >= width) {
					if (map[relative_pos_y][relative_pos_x + 1] != '#') {
						return Direction::RIGHT;
					}
				} else if (y < 0) {
					if (map[relative_pos_y - 1][relative_pos_x] != '#') {
						return Direction::UP;
					}
				} else if (x < 0) {
					if (map[relative_pos_y][relative_pos_x - 1] != '#') {
						return Direction::LEFT;
					}
				} else if (y >= height) {
					if (map[relative_pos_y + 1][relative_pos_x] != '#') {
						return Direction::DOWN;
					}
				}

				if (relative_pos_x + 2 < width && map[relative_pos_y][relative_pos_x + 2] == 0 &&
					map[relative_pos_y][relative_pos_x + 1] != '#') {
					return Direction::RIGHT;
				} else if (relative_pos_y - 2 >= 0 && map[relative_pos_y - 2][relative_pos_x] == 0 &&
						   map[relative_pos_y - 1][relative_pos_x] != '#') {
					return Direction::UP;
				} else if (relative_pos_x - 2 >= 0 && map[relative_pos_y][relative_pos_x - 2] == 0 &&
						   map[relative_pos_y][relative_pos_x - 1] != '#') {
					return Direction::LEFT;
				} else if (relative_pos_y + 2 < height && map[relative_pos_y + 2][relative_pos_x] == 0 &&
						   map[relative_pos_y + 1][relative_pos_x] != '#') {
					return Direction::DOWN;
				}
			}
		}

		return Direction::null;
	}

private:
	void shiftDown() {
		if (strlen(map[height - 1]) > 0) {
			height++;
			map = (char **) realloc(map, height * sizeof(char *));
			if (map == nullptr)
				exit(MEMORY_ERROR);

			map[height - 1] = (char *) calloc(width, sizeof(char));
			if (map[height - 1] == nullptr)
				exit(MEMORY_ERROR);
		}

		auto last = map[height - 1];
		for (int i = height - 1; i > 0; i--)
			map[i] = map[i - 1];
		map[0] = last;
		memset(map[0], 0, width * sizeof(char));
	}

	void shiftRight() {
		for (int y = 0; y < height; y++) {
			if (map[y][width - 1] != 0) {
				width *= 2;

				for (y = 0; y < height; y++) {
					map[y] = (char *) realloc(map[y], width * sizeof(char));
					if (map[y] == nullptr)
						exit(MEMORY_ERROR);

					for (int x = width / 2; x < width; x++)
						map[y][x] = 0;
				}

				break;
			}
		}

		for (int y = 0; y < height; y++) {
			for (int x = width - 1; x > 0; x--)
				map[y][x] = map[y][x - 1];
			map[y][0] = 0;
		}
	}
};

void move(Direction dir) {
	switch (dir) {
		case Direction::RIGHT:
			right();
			break;
		case Direction::UP:
			up();
			break;
		case Direction::LEFT:
			left();
			break;
		case Direction::DOWN:
			down();
		default:
			break;
	}
}

[[nodiscard]] Direction opposite(Direction dir) {
	switch (dir) {
		case Direction::RIGHT:
			return Direction::LEFT;
		case Direction::UP:
			return Direction::DOWN;
		case Direction::LEFT:
			return Direction::RIGHT;
		case Direction::DOWN:
			return Direction::UP;
		default:
			return Direction::null;
	}
}

Direction getDirectionToMoveAndUpdateStack(Map *const map, std::stack<Direction> *movement_stack) {
	Direction d = map->hasUndiscoveredNeighbors();

	if (d == Direction::null) {
		d = movement_stack->top();
		movement_stack->pop();
		return opposite(d);
	}

	movement_stack->push(d);
	return d;
}

void gotoExitIfInSight(Map *map, char fieldOfView[3][3]) {
	if (fieldOfView[1][2] == 'X')         //exit is right
		right();
	else if (fieldOfView[1][0] == 'X')    //exit is left
		left();
	else if (fieldOfView[0][1] == 'X')    //exit is at top
		up();
	else if (fieldOfView[2][1] == 'X')    //exit is at bottom
		down();
	else if (fieldOfView[0][0] == 'X') {  //exit is at top left
		left();
		up();
		left();
	} else if (fieldOfView[0][2] == 'X') { //exit is at top right;
		right();
		up();
		right();
	} else if (fieldOfView[2][1] == 'X') {  //exit is at bottom left
		left();
		down();
		left();
	} else if (fieldOfView[2][1] == 'X') {  //exit is at bottom right
		right();
		down();
		right();
	}

	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++)
			if (fieldOfView[i][j] == 'X')
				map->set(i - 1, j - 1, 0);
}

void findExit(int subtask, char fieldOfView[3][3]) {
	auto *map = new Map(fieldOfView);
	auto *movement_stack = new std::stack<Direction>;
	movement_stack->push(Direction::null);

	while (true) {
		gotoExitIfInSight(map, fieldOfView);

		Direction dir = getDirectionToMoveAndUpdateStack(map, movement_stack);

		if (dir == Direction::null) {
			exit(NOT_FOUND);
		}

		move(dir);
		map->update(dir, fieldOfView);
	}
}
