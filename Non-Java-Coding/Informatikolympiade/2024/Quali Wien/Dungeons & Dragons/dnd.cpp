#include "dnd.h"

#include <charconv>
#include <iostream>

/*
void findExit();
int numOfDoors();
int takeDoor(int);
void takeNote(std::string);
std::string readNote();
*/

using namespace std;

bool hasFlag(char flag) {
	const string note = readNote();
	const string flags = note.substr(note.find(' ') + 1);
	return flags.find(flag) != string::npos;
}

void setFlag(char flag) {
	if (hasFlag(flag)) return;
	takeNote(readNote() + flag);
}

void unsetFlag(char flag) {
	if (!hasFlag(flag)) return;
	const string note = readNote();
	const string flags = note.substr(note.find(' ') + 1);

	// cout << "[" << note.substr(0, note.find(' ')) << "]" << endl;
	// cout << "[" << flags.substr(0, flags.find(flag)) << "]" << endl;
	// cout << "[" << flags.substr(flags.find(flag) + 1) << "]" << endl;

	takeNote(note.substr(0, note.find(' ') + 1) +
			 flags.substr(0, flags.find(flag)) +
			 flags.substr(flags.find(flag) + 1));
}

void setDoor(int door) {
	const string note = readNote();
	takeNote(to_string(door) + " " + note.substr(note.find(' ') + 1));
}

void dfs(const int door, const bool isEvenRun) {
	cout << "[MYLOG]: dfs(" << door << ", " << isEvenRun << ") [" << readNote()
		 << "]" << endl;

	const int back = door == -1 ? -1 : takeDoor(door);
	const int doors = numOfDoors();

	cout << back << ", " << doors << endl;

	int lastDoor = -1;
	const string note = readNote();
	if (!note.empty()) {
		if (note == "D") goto done;
		lastDoor = stoi(note.substr(0, note.find(' ')));
	}

	if (isEvenRun) {
		if (lastDoor == -1) {
			cout << "[MYLOG]: Invalid note (missing door in even run)" << endl;
			exit(1);
		}

		setFlag('T');
		takeDoor(takeDoor(lastDoor));
		unsetFlag('T');
		return dfs(lastDoor, true);
	}

	if (hasFlag('T')) {
		if (lastDoor == -1) {
			cout << "[MYLOG]: Invalid note (missing door with T-flag)" << endl;
			exit(1);
		}

		unsetFlag('T');
		lastDoor++;
	}

	for (int i = lastDoor == -1 ? 1 : lastDoor; i <= doors; i++) {
		if (i == back) continue;

		cout << i << endl;

		setDoor(i);
		dfs(i, false);
	}

done:

	if (back == -1) {
		cout << "[MYLOG]: Exit not found." << endl;
		exit(1);
	}

	takeNote("D");
	takeDoor(back);
}

void findExit() {
	cout << "BEGIN" << endl;

	const string note = readNote();

	if (note.empty()) {
		takeNote("1 O");
	} else if (hasFlag('O')) {
		unsetFlag('O');
		setFlag('E');
	} else if (hasFlag('E')) {
		unsetFlag('E');
		setFlag('O');
	}

	dfs(-1, hasFlag('E'));

	/*takeNote("1 O");
	setFlag('E');
	unsetFlag('O');
	setFlag('O');
	unsetFlag('O');
	setFlag('O');
	unsetFlag('O');
	setFlag('O');
	unsetFlag('O');
	setFlag('O');
	unsetFlag('O');

	cout << "[" << readNote() << "]" << endl;*/
}
