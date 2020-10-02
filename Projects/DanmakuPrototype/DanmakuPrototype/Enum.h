#pragma once
template <class T>
class Enum {
	class Iterator {
	public:
		Iterator(int v) : value(v) {}
		void operator++() { ++value; }
		bool operator!=(Iterator rhs) { return value != rhs.value; }
		T operator*() const { return static_cast<T>(value); }

	private:
		int value{ 0 };
	};
public:
	Iterator begin() const { return Iterator(static_cast<int>(T::BEGIN)); }
	Iterator end() const { return Iterator(static_cast<int>(T::END) + 1); }
};