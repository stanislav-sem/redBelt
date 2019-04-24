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

class BookingManager {
public:
	BookingManager() : current_time(0) {}

	void Book(long long time, string hotel_name, int client_id, int room_count) {}

	int Clients(string hotel_name) {}

	int Rooms(string hotel_name) {}

private:
	long long current_time;
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BookingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      long long time;
      string hotel_name;
      int client_id;
      int room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else if (query_type == "CLIENTS") {
    	string hotel_name;
    	cin >> hotel_name;
      cout << manager.Clients(hotel_name) << endl;
    } else if (query_type == "ROOMS") {
    	string hotel_name;
    	cin >> hotel_name;
    	cout << manager.Rooms(hotel_name) << endl;
    }
  }
  return 0;
}
