#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <string>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = typename set<T>::iterator;
  const size_t MAX_ELEMENTS = 1'000'000; // максимальное количество элементов

  PriorityCollection () {
	  priority[0].reserve(MAX_ELEMENTS);
  }

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
	  Id result = objects.insert(move(object)).first;
	  priority[0].push_back(result);
	  return result;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
	  for (auto it = range_begin; it != range_end; ++it) {
		  Id tmp_id = Add(*it);
		  *ids_begin = tmp_id;
		  ids_begin++;
	  }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
	  return id >= objects.begin() && id < objects.end();
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
	  return *id;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
      Id tmp_id;
	  for (auto el : priority) {
		  for (size_t i = 0; i < el.second.size(); ++i) {
			  if (el.second[i] == id) {
				  tmp_id = id;
			  }
		  }
	  }
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const;

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax();

private:
  set<T> objects;
  // в map: ключ это приоритет, значение - вектор элементов с приоритетом = ключу
  map<int, vector<Id>> priority;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
