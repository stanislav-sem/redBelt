#include <iostream>
#include "deque.h"
#include "test_runner.h"

using namespace std;

void TestEmpty() {
	Deque<int> d;
	ASSERT(d.Empty());
	ASSERT_EQUAL(d.Size(), 0u);
}

void TestPush() {
	Deque<int> d;
	d.PushBack(42);
	ASSERT_EQUAL(d.Back(), 42);
	d.PushBack(66);
	ASSERT_EQUAL(d.Back(), 66);
	d.PushFront(22);
	ASSERT_EQUAL(d.Front(), 22);
	d.PushFront(33);
	ASSERT_EQUAL(d.Front(), 33);
}

void TestBrac() {
	Deque<int> d;
	d.PushBack(42);
	ASSERT_EQUAL(d[0], 42);
	d.PushBack(66);
	ASSERT_EQUAL(d[1], 66);

	d.PushFront(22);
	ASSERT_EQUAL(d[0], 22);
	d.PushFront(33);
	ASSERT_EQUAL(d[1], 22);
	ASSERT_EQUAL(d[0], 33);

	ASSERT_EQUAL(d[2], 42);
	ASSERT_EQUAL(d[3], 66);

	d[1] = 666;
	ASSERT_EQUAL(d[1], 666);
}

void TestAt() {
	Deque<string> d;
	d.PushBack("aaa");
	ASSERT_EQUAL(d.At(0), "aaa");
	d.PushBack("bbb");
	ASSERT_EQUAL(d.At(1), "bbb");

	d.PushFront("ccc");
	ASSERT_EQUAL(d.At(0), "ccc");
	d.PushFront("ddd");
	ASSERT_EQUAL(d.At(1), "ccc");
	ASSERT_EQUAL(d.At(0), "ddd");

	ASSERT_EQUAL(d.At(2), "aaa");
	ASSERT_EQUAL(d.At(3), "bbb");

	d.At(1) = "zzz";
	ASSERT_EQUAL(d.At(1), "zzz");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestEmpty);
	RUN_TEST(tr, TestPush);
	RUN_TEST(tr, TestBrac);
	RUN_TEST(tr, TestAt);
}
