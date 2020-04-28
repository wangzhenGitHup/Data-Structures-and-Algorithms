#pragma once

namespace SelfSTL
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(T1()), second(T2()) {}

		template<class U, class V>
		pair(const pair<U, V>& p) : first(p.first), second(p.second) {}

		bool operator==(const pair<T1, T2>& x)
		{
			return x.first == first && x.second == second;
		}

		bool operator<(const pair<T1, T2>& x)
		{
			return x.first < first ||
				(!(first < x.first) && x.second < second);
		}
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(const T1& x, const T2& y)
	{
		return pair<T1, T2>(x, y);
	}
}