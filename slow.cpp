#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <deque>
#include <map>
#include "test_runner.h"

using namespace std;

struct Order {
	int64_t time;
	string hotel_name;
	unsigned long client_id;
	unsigned long room_count;
};

class BookingManager {
public:
	BookingManager() : current_time(0), BookData(), rooms_count(), clients_count() {}

	void Book(int64_t inp_time, string inp_hotel_name, unsigned long inp_client_id, unsigned long inp_room_count) {
		current_time = inp_time; // сохраняем текущее время
		int64_t day = current_time - 86400;
		while(BookData.front().time <= day && !BookData.empty()) {  // удаляем брони сделанные больше суток назад
			rooms_count[BookData.front().hotel_name] -= BookData.front().room_count;
			clients_count[BookData.front().hotel_name].erase(BookData.front().client_id);
			BookData.pop_front();
		}
		BookData.push_back({inp_time, inp_hotel_name, inp_client_id, inp_room_count}); // сохраняем бронь отеля
		rooms_count[inp_hotel_name] += inp_room_count;  // сохраняем количество занятых комнат для этого отеля
		clients_count[inp_hotel_name].insert(inp_client_id); // сохраняем количество разных клиентов для этого отеля

	}

	int Clients(string inp_hotel_name) {
		return clients_count[inp_hotel_name].size();
	}

	int Rooms(string inp_hotel_name) {
		return rooms_count[inp_hotel_name];
	}

private:
	int64_t current_time;
	deque<Order> BookData;
	map<string, unsigned long> rooms_count;
	map<string, set<unsigned long>> clients_count;
};

//void PrintBook(const BookingManager& input) {
//	for (auto& el : input.BookData) {
//		cout << "time: " << el.time << "; hotel name: " << el.hotel_name
//			 << "; client_id: " << el.client_id << "; room count: " << el.room_count << endl;
//	}
//}
//
//void PrintClients(map<string, set<unsigned long>> input) {
//	for (auto& el : input) {
//		cout << el.first<< ": ";
//		for (auto& v : el.second) {
//			cout << v << " ";
//		}
//		cout << endl;
//	}
//}

void TestFirst() {
	BookingManager bm;
	ASSERT_EQUAL(bm.Clients("Marriot"), 0);
	ASSERT_EQUAL(bm.Rooms("Marriot"), 0);
	bm.Book(10, "FourSeasons", 1, 2);
	bm.Book(10, "Marriott", 1, 1);
	bm.Book(86409, "FourSeasons", 2, 1);
	ASSERT_EQUAL(bm.Clients("FourSeasons"), 2);
	ASSERT_EQUAL(bm.Rooms("FourSeasons"), 3);
	ASSERT_EQUAL(bm.Clients("Marriott"), 1);
	bm.Book(86410, "Marriott", 2, 10);
	ASSERT_EQUAL(bm.Rooms("FourSeasons"), 1);
	ASSERT_EQUAL(bm.Rooms("Marriott"), 10);
}

void TestSecond() {
	BookingManager bm;
	bm.Book(-10'000'000'000'000'000, "azaza", 1, 5);
//	PrintClients(bm.clients_count);
//	PrintBook(bm);
	ASSERT_EQUAL(bm.Clients("azaza"), 1);
	ASSERT_EQUAL(bm.Rooms("azaza"), 5);
	bm.Book(0, "azaza", 66, 1);
//	PrintClients(bm.clients_count);
//	PrintBook(bm);
	ASSERT_EQUAL(bm.Rooms("azaza"), 1);
	ASSERT_EQUAL(bm.Clients("azaza"), 1);
}

int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  TestRunner tr;
  RUN_TEST(tr, TestFirst);
  RUN_TEST(tr, TestSecond);

  BookingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
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
