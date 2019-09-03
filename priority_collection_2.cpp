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
	  vec_priority[0].reserve(MAX_ELEMENTS);
  }

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
	  Id result = objects.insert(move(object)).first;
	  vec_priority[0].push_back(result);
	  map_priority[result] = 0;
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
	  return id >= objects.begin() && id < objects.end();
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
	  return *id;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
     int priority = map_priority[id]++;
     auto it = find(vec_priority[priority].begin(), vec_priority[priority].end(), id);
     vec_priority[priority].erase(it);

     if (vec_priority.size() <= ++priority) {
    	 vec_priority.push_back({id});
     } else {
    	 vec_priority[priority].push_back(id);
     }
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
	  return make_pair(vec_priority.back().back(), vec_priority.size()-1);
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
	  Id id = vec_priority.back().back();
	  int priority = map_priority[id];
	  vec_priority.back().erase(vec_priority.back().end() - 1);
	  map_priority[id] = 0;
	  return make_pair(move(*id), priority);
  }

private:
  set<T> objects;
  vector<vector<Id>> vec_priority;
  map<Id, int> map_priority;
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
