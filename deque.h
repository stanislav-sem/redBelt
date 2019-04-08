#include<vector>
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
			return vFront[index];
		} else if (index < vFront.size() + vBack.size() - 2) {
			return vBack[index-vFront.size()];
		} else {
			throw out_of_range("no index");
		}
	}

	const T& operator[] (size_t index) const {
		if (index < vFront.size()) {
			return vFront[index];
		} else if (index < vFront.size() + vBack.size() - 2) {
			return vBack[index-vFront.size()];
		} else {
			throw out_of_range("no index");
		}
	}

	typename vector<T>::iterator At(size_t index) {

	}

private:
	vector<T> vFront;
	vector<T> vBack;
};
