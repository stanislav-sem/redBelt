#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) { out << (x) << endl << (y) << endl; }

void TestFor() {
	{
		ostringstream xxx;
		PRINT_VALUES(xxx, 1, 2);
		ASSERT_EQUAL(xxx.str(), "1\n2\n");
	}
	{
		ostringstream xxx;
		for (int i = 0; i < 5; ++i) {
			PRINT_VALUES(xxx, i, i+1);
			xxx << end
		}
		ASSERT_EQUAL(xxx.str(), "1/5\n2/5\n3/5\n4/5\n5/5\n");
	}

}



int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");

  RUN_TEST(tr, TestFor);
}

