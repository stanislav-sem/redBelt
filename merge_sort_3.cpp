#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename T>
void PrintVec (vector<T> input) {
	cout << '{';
	bool is_first = true;
	for (auto el : input) {
		if (!is_first) {
			cout << ',';
			is_first = false;
		}
		cout << el;
	}
	cout << '}' << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin < 2) {

  } else {
	  vector<typename RandomIt::value_type> vec(make_move_iterator(range_begin), make_move_iterator(range_end));
	  size_t part_size = vec.size() / 3;

	  vector<typename RandomIt::value_type> tmp1(make_move_iterator(vec.begin()), make_move_iterator(vec.begin() + part_size));
	  MergeSort(tmp1.begin(), tmp1.end());
	  vector<typename RandomIt::value_type> tmp2(make_move_iterator(tmp1.end()), make_move_iterator(tmp1.end() + part_size));
	  MergeSort(tmp2.begin(), tmp2.end());
	  vector<typename RandomIt::value_type> tmp3(make_move_iterator(tmp2.end()), make_move_iterator(tmp2.end() + part_size));
	  MergeSort(tmp3.begin(), tmp3.end());

	  vector<typename RandomIt::value_type> tmp12;
	  merge(make_move_iterator(tmp1.begin()), make_move_iterator(tmp1.end()),
			make_move_iterator(tmp2.begin()), make_move_iterator(tmp2.end()),
			back_inserter(tmp12)
			);
	  merge(make_move_iterator(tmp12.begin()), make_move_iterator(tmp12.end()),
			make_move_iterator(tmp3.begin()), make_move_iterator(tmp3.end()),
			range_begin);
  }
}


void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
//  PrintVec(numbers);
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
