#include "test_runner.h"

#include <vector>

using namespace std;

template <typename T>
class Table {
private:
	vector<vector<T>> cont;


public:
	Table(size_t c, size_t r) {
		Resize(c, r);
	}

	const vector<T>& operator [] (const size_t& i) const {
		return cont[i];
	}
	vector<T>& operator [] (const size_t& i) {
		return cont[i];
	}

	void Resize(size_t c, size_t r) {
		cont.resize(c);
		for (auto& el : cont) {
			el.resize(r);
		}
	}

	pair<size_t , size_t> Size() const {
		size_t first = cont.size();
		size_t second = cont.empty() ? 0 : cont[0].size();
		return make_pair(first, second);
	}
};


void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t.Resize(3, 4);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
