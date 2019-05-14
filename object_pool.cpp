#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <vector>
using namespace std;

template<class T>
class ObjectPool {
public:
	ObjectPool() : active(), free() {};

	T* Allocate() {
		if (!free.empty()) {
			active.push_back(free.front());
			free.pop_front();
			return active.back();
		}
		else {
			T* pT = new T;
			active.push_back(pT);
			return pT;
		}
	}

	T* TryAllocate() {
		if (!free.empty()) {
			active.push_back(free.front());
			free.pop_front();
			return active.back();
		} else {
			return nullptr;
		}
	}

	void Deallocate(T* object) {
		auto it = find(active.begin(), active.end(), object);
		if (it == active.end()) {
			throw invalid_argument("No such object!");
		}
		free.push_back(*it);
		active.erase(it);
	}

	~ObjectPool() {
		while(!active.empty()) {
			delete active.front();
			active.erase(active.begin());
		}
		while(!free.empty()) {
			delete free.front();
			free.erase(free.begin());
		}

	};

private:
	deque<T*> active;
	deque<T*> free;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
