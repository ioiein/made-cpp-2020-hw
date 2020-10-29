#pragma once
#include <vector>
#include <iostream>


namespace task {

template <class T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
	std::vector<T> c(a.size());
	for (size_t i = 0; i < a.size(); ++i) {
		c[i] = a[i] + b[i];
	}
	return c;
}
	
template <class T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b) {
	std::vector<T> c(a.size());
	for (size_t i = 0; i < a.size(); ++i) {
		c[i] = a[i] - b[i];
	}
	return c;
}

template <class T>
std::vector<T> operator-(const std::vector<T>& a) {
	std::vector<T> c(a.size());
	for (size_t i = 0; i < a.size(); ++i) {
		c[i] = -a[i];
	}
	return c;
}

template <class T>
std::vector<T> operator+(const std::vector<T>& a) {
	return a;
}
	
template <class T>
T operator*(const std::vector<T>& a, const std::vector<T>& b) {
	T c = 0;
	for (size_t i = 0; i < a.size(); ++i) {
		c += a[i] * b[i];
	}
	return c;
}
	
template <class T>
std::vector<T> operator%(const std::vector<T>& a, const std::vector<T>& b) {
	std::vector<T> c(3);
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	return c;	
}
	
const double ALPHA = 1e-7;
template <class T>
bool operator||(const std::vector<T>& a, const std::vector<T>& b) {
	size_t i;
	for (i = 0; i < a.size(); ++i) {
		if (a[i] != 0 && b[i] != 0) { break; }
	}
	if (i == a.size() || a[i] == 0 || b[i] == 0) { return false; }
	double k = a[i] * 1.0 / b[i];
	while (++i != a.size())
		if (a[i] - b[i] * k > ALPHA || b[i] * k - a[i] > ALPHA) { return 0; }
	return true;
}

template <class T>
bool operator&&(const std::vector<T>& a, const std::vector<T>& b) {
	return (a * b > 0) && (a || b);
}
	
template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		os << a[i] << ' ';
	}
	os << '\n';
	return os;
}

template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& a) {
	size_t n;
	is >> n;
	a.resize(n);
	T buff;
	for (size_t i = 0; i < n; ++i) {
		is >> buff;
		a[i] = buff;
	}
	return is;
}

template <class T>
void reverse(std::vector<T>& a) {
	for (size_t i = 0; i < a.size() / 2; ++i) {
		std::swap(a[i], a[a.size() - 1 - i]);
	}
}

std::vector<int> operator|(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<int> c(a.size());
	for (size_t i = 0; i < a.size(); ++i) {
		c[i] = a[i] | b[i];
	}
	return c;
}

std::vector<int> operator&(const std::vector<int>& a, const std::vector<int>& b){
	std::vector<int> c(a.size());
	for (size_t i = 0; i < a.size(); ++i) {
		c[i] = a[i] & b[i];
	}
	return c;
}

}  // namespace task
