#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) {
	  if (a_size > N) {
		  throw invalid_argument("Array size bigger than array capacity.");
	  } else {
		  datasize = a_size;
	  }
  }

  T& operator[](size_t index) { return data[index]; }
  const T& operator[](size_t index) const {return data[index]; }

  auto begin() { data.begin(); }
  auto end() { data.begin() + datasize; }
  auto begin() const { data.begin(); }
  auto end() const { data.begin() + datasize; }

  size_t Size() const {return datasize; };
  size_t Capacity() const { return N; }

  void PushBack(const T& value) {
	  if (datasize == N) {
		  throw overflow_error("No more memory.");
	  } else {
		  data[datasize++] = value;
	  }
  }
  T PopBack() {
	  if (datasize == 0) {
		  throw underflow_error("No elements.");
	  } else {
		  return data[--datasize];
	  }
  }

private:
  array<T, N> data;
  size_t datasize;
};

