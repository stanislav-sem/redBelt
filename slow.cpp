#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        page_rating(1000),
		user_count(0) {}


  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
    	page_rating[0].insert(user_id);
		++user_count;
    }
    user_page_counts_[user_id] = page_count;
    page_rating[page_count].insert(user_id);
    for (int i = 0; i < page_count; i++) {
    	auto it = page_rating[i].find(user_id);
    	if (it != page_rating[i].end()) {
    		page_rating[i].erase(it);
    		break;
    	}
    }
  }


  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int remain_user = 0;
    for  (int i = 1; i < page_count; i++) {
    	remain_user += page_rating[i].size();
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (user_count - remain_user) * 1.0 / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<set<int>> page_rating;
  int user_count;
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
