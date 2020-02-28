#pragma once

namespace SelfSTL
{
	template<class T>
	inline const T& min(const T& a, const T& b)
	{
		return b < a ? b : a;
	}

	template<class T>
	inline const T& max(const T& a, const T& b)
	{
		return a < b ? b : a;
	}

	template<class T, class Compare>
	inline const T& min(const T& a, const T& b, Compare comp)
	{
		return comp(b, a) ? b : a;
	}

	template<class T, class Compare>
	inline const T& max(const T& a, const T& b, Compare comp)
	{
		return comp(a, b) ? b : a;
	}

	template<class T>
	inline void swap(T& a, T& b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}

	/*
	//example

	bool int_ptr_less(int* a, int* b)
	{
		return *a < *b;
	}

	int main()
	{
		int x = 17;
		int y = 42;
		int* px = &x;
		int* py = &y;
		int* pmax;
		pmax = max(px, py, int_ptr_less);
	}*/

	namespace rel_ops
	{
		template<class T>
		inline bool operator != (const T& x, const T& y)
		{
			return !(x == y);
		}

		template<class T>
		inline bool operator > (const T& x, const T& y)
		{
			return y < x;
		}

		template<class T>
		inline bool operator >= (const T& x, const T& y)
		{
			return !(x < y);
		}

		template<class T1, class T2>
		inline bool operator != (const T1& x, const T2& y)
		{
			return !(x == y);
		}
	}
}