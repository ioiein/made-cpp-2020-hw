#pragma once
#include <vector>
#include <iostream>


namespace task {

	template <class T>
	std::vector<T> operator+ (const std::vector<T>& a, const std::vector<T>& b)
	{
		std::vector<T> c;
		c.reserve(a.size());
		for (size_t i = 0; i < a.size(); ++i)
		{
			c.push_back(a[i] + b[i]);
		}
		return c;
	}
	
	template <class T>
	std::vector<T> operator- (const std::vector<T>& a, const std::vector<T>& b)
	{
		std::vector<T> c;
		c.reserve(a.size());
		for (size_t i = 0; i < a.size(); ++i)
		{
			c.push_back(a[i] - b[i]);
		}
		return c;
	}

	template <class T>
	std::vector<T> operator- (const std::vector<T>& a)
	{
		std::vector<T> c;
		c.reserve(a.size());
		for (size_t i = 0; i < a.size(); ++i)
		{
			c.push_back(-a[i]);
		}
		return c;
	}

	template <class T>
	std::vector<T> operator+ (const std::vector<T>& a)
	{
		return a;
	}
	
	template <class T>
	T operator* (const std::vector<T>& a, const std::vector<T>& b)
	{
		T c = 0;
		for (size_t i = 0; i < a.size(); ++i)
		{
			c += a[i] * b[i];
		}
		return c;
	}
	
	template <class T>
	std::vector<T> operator% (const std::vector<T>& a, const std::vector<T>& b)
	{
		std::vector<T> c;
		c.push_back(a[1] * b[2] - a[2] * b[1]);
		c.push_back(a[2] * b[0] - a[0] * b[2]);
		c.push_back(a[0] * b[1] - a[1] * b[0]);
		return c;	
	}
	
	const double ALPHA = 1e-7;
	template <class T>
	bool operator|| (const std::vector<T>& a, const std::vector<T>& b)
	{
		for (size_t i = 1; i < a.size(); ++i)
		{
			if ((double)b[i - 1] / a[i - 1] - (double)b[i] / a[i] > ALPHA || 
			(double)b[i] / a[i] - (double)b[i - 1] / a[i - 1] > ALPHA)
			{
				return false;
			}
		}
		return true;
	}

	template <class T>
	bool operator&& (const std::vector<T>& a, const std::vector<T>& b)
	{
		return (a * b > 0) && (a || b);
	}
	
	template <class T>
	std::ostream& operator<< (std::ostream& os, const std::vector<T>& a)
	{
		for (size_t i = 0; i < a.size(); ++i)
		{
			os << a[i] << ' ';
		}
		os << '\n';
		return os;
	}

	template <class T>
	std::istream& operator>> (std::istream& is, std::vector<T>& a)
	{
		a.clear();
		int n;
		is >> n;
		T buff;
		for (size_t i = 0; i < n; ++i)
		{
			is >> buff;
			a.push_back(buff);
		}
		return is;
	}

	template <class T>
	void reverse (std::vector<T>& a)
	{
		for (size_t i = 0; i < a.size() / 2; ++i)
		{
			std::swap(a[i], a[a.size() - 1 - i]);
		}
	}

	std::vector<int> operator| (const std::vector<int>& a, const std::vector<int>& b)
	{
		std::vector<int> c;
		c.reserve(a.size());
		for (size_t i = 0; i < a.size(); ++i)
		{
			c.push_back(a[i] | b[i]);
		}
		return c;
	}

	std::vector<int> operator& (const std::vector<int>& a, const std::vector<int>& b)
	{
		std::vector<int> c;
		c.reserve(a.size());
		for (size_t i = 0; i < a.size(); ++i)
		{
			c.push_back(a[i] & b[i]);
		}
		return c;
	}

		


}  // namespace task
