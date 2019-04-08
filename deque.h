#include<vector>
#include<iostream>
#include<stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() : vFront(), vBack() {};

	bool Empty() const {
		return (vFront.empty() && vBack.empty());
	}

	size_t Size() const {
		return vFront.size() + vBack.size();
	}

	T& operator[] (size_t index) {
		if (index < vFront.size()) {
			return vFront.at(index);
		} else if (index < vFront.size() + vBack.size()) {
			return vBack.at(index - vFront.size());
		} else {
			throw out_of_range("no index in op[]");
		}
	}
	const T& operator[] (size_t index) const {
		if (index < vFront.size()) {
			return vFront.at(index);
		} else if (index < vFront.size() + vBack.size()) {
			return vBack.at(index - vFront.size());
		} else {
			throw out_of_range("no index in const op[]");
		}
	}


	T& At(size_t index) {
		if (index < vFront.size()) {
			return vFront.at(index);
		} else if (index < vFront.size() + vBack.size()) {
			return vBack.at(index - vFront.size());
		} else {
			throw out_of_range("no index in .At()");
		}
	}
	const T& At(size_t index) const {
		if (index < vFront.size()) {
			return vFront.at(index);
		} else if (index < vFront.size() + vBack.size()) {
			return vBack.at(index - vFront.size());
		} else {
			throw out_of_range("no index in const .At()");
		}
	}


	const T& Front () const {
		if (!vFront.empty()) {
			return vFront[0];
		} else if (!vBack.empty()) {
			return vBack[0];
		} else {
			throw out_of_range("no index in const Front");
		}
	}
	T& Front() {
		if (!vFront.empty()) {
			return vFront[0];
		} else if (!vBack.empty()) {
			return vBack[0];
		} else {
			throw out_of_range("no index in Front");
		}
	}

	const T& Back () const {
		if (!vBack.empty()) {
			return vBack[vBack.size()-1];
		} else if (!vFront.empty()) {
			return vFront[vFront.size()-1];
		}
		else {
			throw out_of_range("no index in const Back");
		}
	}
	T& Back() {
		if (!vBack.empty()) {
			return vBack[vBack.size() - 1];
		} else if (!vFront.empty()) {
			return vFront[vFront.size() - 1];
		} else {
			throw out_of_range("no index in Back");
		}
	}

	void PushFront(const T& value) {
		vFront.insert(vFront.begin(), value);
	}
	void PushBack(const T& value) {
		vBack.push_back(value);
	}

private:
	vector<T> vFront;
	vector<T> vBack;
};
