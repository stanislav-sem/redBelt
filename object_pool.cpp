#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template<class T>
class ObjectPool {
public:
	ObjectPool() : all(), deAll() {};

	T* Allocate() {
		if (!deAll.empty()) {
			all.push_back(deAll.front());
			deAll.pop();
		}
	return all.back();
	}

	T* TryAllocate();

	void Deallocate(T* object);

	~ObjectPool();

private:
	deque<T*> all;
	deque<T*> deAll;
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
