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
  using Id = typename map<T, int>::iterator;
  const size_t MAX_ELEMENTS = 1'000'000; // максимальное количество элементов

  PriorityCollection () {
	  priorities[0].reserve(MAX_ELEMENTS);
  }

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
	  Id result = (container.insert({move(object), 0})).first;
	  priorities[0].push_back(result);
	  return result;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
	  for (auto it = range_begin; it != range_end; ++it) {
		  *ids_begin = Add(*it);
		  ids_begin++;
	  }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
	  return id >= container.begin() && id < container.end();
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
	  return (*id)->first;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
	  (*id).second++;
	  for (auto it1 = priorities.begin(); it1 != priorities.end(); ++it1) {
		  auto it2 = find((*it1).begin(), (*it1).end(), id);
		  if (it2 != (*it1).end()) {
			  (*it1).erase(it2);
			  ++it1;
			  (*it1).push_back(id);
			  return;
		  }
	  }
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
	  Id id = priorities.back().back();
	  return *id;
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
	 Id id = priorities.back().back();
	 priorities.back().pop_back();
	 auto tmp = priorities.extract(id);
  }

private:
//  set<T> objects;
//  vector<vector<Id>> vec_priority;
//  map<Id, int> map_priority;
  map<T, int> container;
  vector<vector<Id>> priorities;

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
