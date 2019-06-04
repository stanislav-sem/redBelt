#include <iostream>
#include<list>
#include<map>
#include<algorithm>

using namespace std;

/*
5
42 0
17 42
13 0
123 42
5 13

17 123 42 5 13
 */

void PrintList(list<int> ls) {
//	cout << '{';
	for (auto el : ls) {
		cout << el << ' ';
	}
//	cout << "}\n";
}

int main() {
	int Q = 0; cin >> Q; //количество пар
	list<int> line;
	map<int, list<int>::iterator> numbers; //словарь для хранения итераторов на игроков

	for (int i = 1; i <= Q; ++i) {
		int next, prev; // номера очередного выходящего спортсмена, и того перед которым нужно встать.
		cin >> next >> prev;
		try {
			auto it = numbers.at(prev);
			auto newit = line.insert(it, next);
			numbers[next] = newit;
		} catch(out_of_range& ex) {
			auto newit = line.insert(line.end(), next);
			numbers[next] = newit;
		}


	}
	PrintList(line);
	return 0;
}
