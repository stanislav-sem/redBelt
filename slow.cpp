#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <deque>
#include <map>

using namespace std;

struct Order {
	long long time;
	string hotel_name;
	int client_id;
	int room_count;
};

class BookingManager {
public:
	BookingManager() : current_time(0), BookData(), rooms_count(), clients_count() {}

	void Book(long long inp_time, string inp_hotel_name, int inp_client_id, int inp_room_count) {
		current_time = inp_time; // сохраняем текущее время
		long long day = current_time - 86400;
		while(BookData.front().time <= day) {  // удаляем брони сделанные больше суток назад
			rooms_count[BookData.front().hotel_name] -= BookData.front().room_count;
			clients_count[BookData.front().hotel_name].erase(BookData.front().client_id);
			BookData.pop_front();
		}
		BookData.push_back({inp_time, inp_hotel_name, inp_client_id, inp_room_count}); // сохраняем бронь отеля
		rooms_count[inp_hotel_name] += inp_room_count;  // сохраняем количество занятых комнат для этого отеля
		clients_count[inp_hotel_name].insert(inp_client_id);

	}

	int Clients(string inp_hotel_name) {
//		int result = 0;
//		set<int> unique_id;
//		for (size_t i = 0; i < BookData.size(); i++) {
//			if(BookData[i].hotel_name == inp_hotel_name) {
//				unique_id.insert(BookData[i].client_id);
//			}
//		}
//		result = unique_id.size();
		return clients_count[inp_hotel_name].size();
	}

	int Rooms(string inp_hotel_name) {
//		int result = 0;
//		for (size_t i = 0; i < BookData.size(); i++) {
//			if(BookData[i].hotel_name == inp_hotel_name) {
//				result += BookData[i].room_count;
//			}
//		}
//		return result;
		return rooms_count[inp_hotel_name];
	}

private:
	long long current_time;
	deque<Order> BookData;
	map<string, int> rooms_count;
	map<string, set<int>> clients_count;
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
