#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

/*
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }

}
 */
ostream& operator << (ostream& os, const Date& date) {
	os << date.year << "-" << date.month << "-" << date.day;
	return os;
}

ostream& operator << (ostream& os, const Time& time) {
	os << time.hours << ":" << time.minutes;
	return os;
}

bool operator == (const Date& lhs, const Date& rhs) {
	return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator == (const Time& lhs, const Time& rhs) {
	return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

istream& operator >> (istringstream& is, Date& date) {
	is >> date.year;
	is.ignore(1);
	is >> date.month;
	is.ignore(1);
	is >> date.day;
	return is;
}

istream& operator >> (istringstream& is, Time& time) {
	is >> time.hours;
	is.ignore(1);
	is >> time.minutes;
	return is;
}


#define UPDATE_FIELD(ticket, field, values) {   \
	auto it = values.find(#field);				\
	if(it != values.end()) {					\
	istringstream is(it->second); 				\
	is >> ticket.field;							\
	} 											\
}

void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates);

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 РЅ// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
