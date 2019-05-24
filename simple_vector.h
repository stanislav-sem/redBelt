#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() {
	  data_ = nullptr;
	  vecSize = 0;
  }

  explicit SimpleVector(size_t size) {
	  data_ = new T[size];
	  vecSize = size;
  }
  ~SimpleVector() {
	  delete[] data_;
  }

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const {
	  return vecSize;
  }
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  // Добавьте поля для хранения данных вектора
  T* data_;
  size_t vecSize;
};
