#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() {
	  data_ = nullptr;
	  end_ = nullptr;
	  endOfArea = nullptr;
  }

  explicit SimpleVector(size_t size) {
	  data_ = new T[size];
	  end_ = data_ + size;
	  endOfArea = end_;
  }
  ~SimpleVector() {
	  delete[] data_;
  }

  T& operator[](size_t index) {
	  return data_[index];
  }

  T* begin() {return data_;}
  T* end()   {return end_;}
  const T* begin() const {return data_;}
  const T* end()   const {return end_;}

  size_t Size() const {
	  return end_ - data_;
  }
  size_t Capacity() const {
	  return endOfArea - data_;
  }
  void PushBack(const T& value) {
	  if (Size() == Capacity()) {
		  T* tmpData = nullptr;
		  if (Capacity() == 0) {
			  tmpData = new T[1];
			  endOfArea = tmpData + 1;
		  } else {
				tmpData = new T[2 * Capacity()];
				endOfArea = tmpData + 2 * Capacity();
		  }
		  T* tmp_end_ = std::copy(data_, end_, tmpData);
		  delete[] data_;
		  data_ = tmpData;
		  *tmp_end_ = value;
		  end_ = ++tmp_end_;
	  } else {
		  *end_ = value;
		  end_++;
	  }
  }

private:
  T* data_;
  T* end_;
  T* endOfArea;
};
