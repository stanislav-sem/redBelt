#include <iostream>
#include "deque.h"
#include "test_runner.h"

using namespace std;

void TestEmpty() {
	Deque<int> d;
	ASSERT(d.Empty());
	ASSERT_EQUAL(d.Size(), 0u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestEmpty);
}
