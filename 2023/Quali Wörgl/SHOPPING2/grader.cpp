#include "shopping.h"
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <unistd.h>
#include <vector>


template<typename T>
class Channel {
	std::mutex m;
	std::queue<T> q;
	std::condition_variable cv;

public:
	void send(T v) {
		std::lock_guard<std::mutex> lock(m);
		q.push(std::move(v));
		cv.notify_one();
	}

	T receive() {
		std::unique_lock<std::mutex> lock(m);
		while(q.empty())
			cv.wait(lock);
		auto v = std::move(q.front());
		q.pop();
	  return v;
	}
};

namespace {
	int count[2];
	Channel<bool> atob;
	Channel<bool> btoa;
	
	thread_local bool isA;
	thread_local int limit;
	thread_local Channel<bool> *readpipe;
	thread_local Channel<bool> *writepipe;
}

void send(bool b) {
	if(++count[isA] > limit) {
		std::cout << "Maximum number of bits exceeded by "
			<< (isA ? "Alice" : "Bob") << "\n";
		std::exit(1);
	}
	writepipe->send(b);
}

bool receive() {
	return readpipe->receive();
}

int main() {
	int n, l, r;
	std::cin >> n >> l >> r;
	std::vector<int> p(n);
	for (int& x : p)
		std::cin >> x;

	int result;
	std::thread a([=] {
		isA = true;
		limit = 10000;
		writepipe = &atob;
		readpipe = &btoa;
		alice(p);
	});
	std::thread b([=, &result] {
		isA = false;
		limit = 18;
		writepipe = &btoa;
		readpipe = &atob;
		result = bob(n, l, r);
	});
	a.join();
	b.join();

	int min_idx = std::min_element(p.begin() + l,
			p.begin() + r + 1) - p.begin();
	if (result != min_idx) {
		std::cout << "wrong, " << result << " instead of "
			<< min_idx << "\n";
		return 1;
	}
	std::cout << "ok, " << count[0] << " " << count[1] << "\n";
	return 0;
}
