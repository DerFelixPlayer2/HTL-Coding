#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

void splitOnSpace(std::string const &str, char **out) {
	std::stringstream ss(str);
	std::string word;
	for (int i = 0; ss >> word; i++)
		strcpy(out[i], word.c_str());
}

void splitOnSpaceAndToInt(std::string const &str, int out[]) {
	std::stringstream ss(str);
	std::string word;
	for (int i = 0; ss >> word; i++)
		out[i] = std::stoi(word);
}

long long partialSum(int from, int to) {
	return (long long) ((double) (to - from + 1LL) * (((double) from + (double) to) / 2LL));
}

void swap(int *pool, int i, int j) {
	auto tmp = pool[i];
	pool[i] = pool[j];
	pool[j] = tmp;
}

void bubbleUp(int *pool, int max, int i) {
	int v = pool[i];

	for (int j = i; j < max; j++) {
		pool[j] = pool[j + 1];
	}

	pool[max - 1] = v;
}

long long calculateVolume(const int *values, const int max) {
	long long sum = 0;
	int highest;

	if (values[0] == max) {
		highest = values[max - 1];
		for (int i = max - 1; i >= 0; i--) {
			if (values[i] > highest) {
				highest = values[i];
				continue;
			}

			sum += highest - values[i];
		}
	} else if (values[max - 1] == max) {
		highest = values[0];
		for (int i = 1; i < max; i++) {
			if (values[i] > highest) {
				highest = values[i];
				continue;
			}

			sum += highest - values[i];
		}
	} else {
		highest = values[max - 1];
		for (int i = max - 1; i >= 0 && highest != max; i--) {
			if (values[i] > highest) {
				highest = values[i];
				continue;
			}

			sum += highest - values[i];
		}

		highest = values[0];
		for (int i = 1; i < max && highest != max; i++) {
			if (values[i] > highest) {
				highest = values[i];
				continue;
			}

			sum += highest - values[i];
		}
	}

	return sum;
}

int *getPoolWithSize(const int max, const long long volume) {
	int *pool = static_cast<int *>(malloc(max * sizeof(int)));

	pool[0] = max;
	for (int i = 1; i < max; i++) {
		pool[i] = i;
	}

	long long vol = partialSum(1, max - 2);

	for (int i = 0, j = 0; vol > volume; i++) {

		if (partialSum(1, max - j - 3) >= volume) {
			swap(pool, j, j + 1);
			j++;
		} else {
			bubbleUp(pool, max, (int) (max - 1LL - (vol - volume)));
			return pool;
		}

		vol = partialSum(1, max - j - 2);
	}

	return pool;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	std::string input;
	char **split = static_cast<char **>(malloc(2 * sizeof(char *)));
	split[0] = static_cast<char *>(malloc(23 * sizeof(char)));
	split[1] = static_cast<char *>(malloc(23 * sizeof(char)));

	std::getline(std::cin, input);
	splitOnSpace(input, split);

	const int n = std::stoi(split[0]);
	const long long wanted_volume = std::stoll(split[1]);

	for (int i = 0; i < 2; i++)
		free(split[i]);
	free(split);
	split = nullptr;

	std::string input_values;
	std::getline(std::cin, input_values);

	int values[n];
	splitOnSpaceAndToInt(input_values, values);

	const long long volume = calculateVolume(values, n);
	const long long diff = std::abs(wanted_volume - volume);

	std::cout << diff << std::endl;

	if (diff != 0LL) {
		long long max_volume = partialSum(1, n - 2);

		if (max_volume < wanted_volume) {
			std::cout << -1 << std::endl;
		} else if (max_volume == wanted_volume) {
			std::cout << n - 1 << " ";
			for (int i = 1; i < n - 1; i++)
				std::cout << i << " ";
			std::cout << n << std::endl;
		} else {
			const int *pool = getPoolWithSize(n, wanted_volume);

			for (int i = 0; i < n; i++)
				std::cout << pool[i] << " ";
		}
	}

	return 0;
}