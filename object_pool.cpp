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
	ObjectPool() : all(), deAll() {};

	T* Allocate() {
		if (!deAll.empty()) {
			all.push_back(deAll.front());
			deAll.pop_front();
			return all.back();
		}
		else {
			T* pT = new T;
			all.push_back(pT);
			return pT;
		}
	}

	T* TryAllocate() {
		if (!deAll.empty()) {
			all.push_back(deAll.front());
			deAll.pop_front();
			return all.back();
		} else {
			return nullptr;
		}
	}

	void Deallocate(T* object) {
		auto it = find(deAll.begin(), deAll.end(), object);
		if (it == deAll.end()) {
			throw invalid_argument("wrong object");
		} else {
			all.push_back(*it);
			deAll.erase(it);
		}
	}

	~ObjectPool() {
		cout << "Desruction"<< endl;
	};

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
//
//  pool.Deallocate(p3);
//  pool.Deallocate(p1);
//  ASSERT_EQUAL(*pool.Allocate(), "third");
//  ASSERT_EQUAL(*pool.Allocate(), "first");
//
//  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
