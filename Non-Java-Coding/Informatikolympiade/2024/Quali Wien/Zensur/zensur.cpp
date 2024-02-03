#include "zensur.h"

void smartAppend(std::string *s1, const std::string &s2);

std::string findBannedWord() {
	std::string hasWord;

	std::string string;

	for (int a = 0; a < 26; a++) {
		for (int b = 0; b < 26; b++) {
			for (int c = 0; c < 26; c++) {
				for (int d = 0; d < 26; d++) {
					if (string.size() == 10000) {
						bool ans = sendMessage(string);
						if (ans) hasWord = string;
						string.clear();
					}

					if (!hasWord.empty()) {
						goto end_loop;
					}

					std::string s;

					s += char('a' + a);
					s += char('a' + b);
					s += char('a' + c);
					s += char('a' + d);

					string += s;
				}
			}
		}
	}

	hasWord = string;

end_loop:

	while (true) {
		std::string left, right;

		// printf("H %d\n", hasWord.size() / 2);
		left = hasWord.substr(0, hasWord.size() / 2);
		right = hasWord.substr(hasWord.size() / 2);

		if (sendMessage(right))
			hasWord = right;
		else if (sendMessage(left))
			hasWord = left;
		else {
			if (left.size() <= 3) {
				hasWord = left;
			} else {
				// printf("L %d %s\n", left.size() - 3, left.c_str());
				hasWord = left.substr(left.size() - 3, 3);
			}

			if (right.size() <= 3) {
				hasWord += right;
			} else {
				// printf("R %d %s\n", right.size(), right.c_str());
				hasWord += right.substr(0, 3);
			}

			for (int i = 0; i < 3; i++) {
				if (sendMessage(hasWord.substr(i, 4)))
					return hasWord.substr(i, 4);
			}
		}

		// printf("F %s\n", hasWord.c_str());
		if (hasWord.size() == 4) {
			return hasWord;
		}
	}
}

void smartAppend(std::string *s1, const std::string &s2) {
	if (s1->size() < 4) {
		s1->append(s2);
		return;
	}

	for (int i = 3; i >= 0; i--) {
		if (s1->substr(s1->size() - i) == s2.substr(0, i)) {
			s1->append(s2.substr(s2.size() - (4 - i)));
			return;
		}
	}

	s1->append(s2);
}