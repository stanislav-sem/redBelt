#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

void PrintVecSet(vector<set<int>> input) {
	cout << '{';
	for (auto el : input) {
		cout << '{';
		for (auto i : el) {
			cout << i << ',';
		}
		cout << '}';
	}
	cout << '}' << endl;
}

class ReadingManager {
public:
	ReadingManager() :
			user_page_counts_(MAX_USER_COUNT_ + 1, 0),
			page_rating(1001) {}

	void Read(int user_id, int page_count) {
		int tmp_page = user_page_counts_[user_id];      // временно запомнили предыдущую страницу
		auto it = page_rating[tmp_page].find(user_id);  // в векторе страниц находим текущего пользователя и
		if (it != page_rating[tmp_page].end()) {        // удаляем предыдущю страницу
			page_rating[tmp_page].erase(it);
		}
		user_page_counts_[user_id] = page_count;        // записали текущую страницу в вектор пользователей
		page_rating[page_count].insert(user_id);        // записали текущую страницу в вектор страниц
	}

	double Cheer(int user_id) const {
		if (user_page_counts_[user_id] == 0) {
			return 0;
		}
		int all_reading_users = 0;
		int less_reading_users = 0;
		for (int i = 1; i < 1001; i++) {
			all_reading_users += page_rating[i].size();
			if (i < user_page_counts_[user_id]) {
				less_reading_users += page_rating[i].size();
			}
		}
		if (all_reading_users == 1) {
			return 1;
		}
//    const int page_count = user_page_counts_[user_id];
//    int remain_user = 0;
//    for  (int i = 1; i < page_count; i++) {
//    	remain_user += page_rating[i].size();
//    }
//    PrintVecSet(page_rating);
//    cout << "all_reading_users: " << all_reading_users << "; less_reading_users: " << less_reading_users << endl;
//    return (all_reading_users - less_reading_users) * 1.0 / (less_reading_users - 1);
		return less_reading_users * 1.0 / (all_reading_users - 1);
	}

private:
	static const int MAX_USER_COUNT_ = 100'000;
	vector<int> user_page_counts_;
	vector<set<int>> page_rating;
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
//      cout << setprecision(6) << manager.Cheer(user_id) << endl;
    }
  }

  return 0;
}
