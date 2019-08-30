#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename T>
void PrintVec (const vector<T>& input) {
	cout << '{';
	bool is_first = true;
	for (auto el : input) {
		if (is_first) {
			is_first = false;
		} else {
			cout << ", ";
		}
		cout << el;
	}
	cout << '}' << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin <= 2) {
	  return;
  } else {
	  vector<typename RandomIt::value_type> vec(make_move_iterator(range_begin), make_move_iterator(range_end));
	  size_t part_size = vec.size() / 3;

	  MergeSort(vec.begin(), vec.begin() + part_size);
	  MergeSort(vec.begin() + part_size, vec.begin() + 2*part_size);
	  MergeSort(vec.begin() + 2*part_size, vec.end());

	  vector<typename RandomIt::value_type> tmp12;
	  tmp12.reserve(2*part_size);
	  merge(make_move_iterator(vec.begin()), make_move_iterator(vec.begin() + part_size),
			make_move_iterator(vec.begin() + part_size), make_move_iterator(vec.begin() + 2*part_size),
			back_inserter(tmp12)
			);
	  merge(make_move_iterator(tmp12.begin()), make_move_iterator(tmp12.end()),
			make_move_iterator(vec.begin() + 2*part_size), make_move_iterator(vec.end()),
			range_begin
			);
  }
}


void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  PrintVec(numbers);
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

void TestIntVector2() {
	vector<int> numbers = {6, 4, 7, 6, 4, 4, 0, 1, 5};
	MergeSort(begin(numbers), end(numbers));
	PrintVec(numbers);
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestIntVector2);
  return 0;
}
