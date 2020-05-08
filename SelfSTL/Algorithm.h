#pragma once

#include <cstring>
#include <utility>

#include "tools.h"
#include "pair.h"
#include "Allocator.h"
#include "Iterator.h"
#include "TypeTraits.h"
#include "Functional.h"

namespace SelfSTL
{
	/*************fill******************/
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
		{
			*first = value;
		}
	}

	inline void fill(char* first, char* last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}

	inline void fill(wchar_t* first, wchar_t* last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}

	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
		{
			*first = value;
		}

		return first;
	}

	template<class Size>
	char* fill_n(char* first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

	template<class Size>
	wchar_t* fill_n(wchar_t* first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	template<class RandomAccessIterator, class Compare>
	static void up(RandomAccessIterator first, RandomAccessIterator last, 
		RandomAccessIterator head, Compare comp)
	{
		if (first != last)
		{
			int idx = last - head;
			auto parentIdx = (idx - 1) / 2;
			for (auto cur = last; parentIdx >= 0 && cur != head; parentIdx = (idx - 1) / 2)
			{
				auto parent = head + parentIdx;
				if (comp(*parent, *cur))
				{
					SelfSTL::swap(*parent, *cur);
				}
				cur = parent;
				idx = cur - head;
			}
		}
	}

	template<class RandomAccessIterator, class Compare>
	static void down(RandomAccessIterator first, RandomAccessIterator last, 
		RandomAccessIterator head, Compare comp)
	{
		if (first != last)
		{
			auto idx = first - head;
			auto leftChildIdx = idx * 2 + 1;
			for (auto cur = first; leftChildIdx < (last - head + 1) && cur < last; leftChildIdx = idx * 2 + 1)
			{
				auto child = head + leftChildIdx;
				if ((child + 1) <= last && *(child + 1) > *child)
				{
					child += 1;
				}

				if (comp(*cur, *child))
				{
					SelfSTL::swap(*cur, *child);
				}
				cur = child;
				idx = cur - head;
			}
		}
	}

	template<class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		SelfSTL::make_heap(first, last, 
			typename SelfSTL::less < SelfSTL::iterator_traits<RandomAccessIterator>::value_type()); 
	}

	template<class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		const auto range = last - first;
		for (auto cur = first + range / 2 - 1; cur >= first; --cur)
		{
			SelfSTL::down(cur, last - 1, first, comp);
			if (cur == first)
			{
				return;
			}
		}
	}


	template<class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		SelfSTL::push_heap(first, last, 
			SelfSTL::less < typename SelfSTL::iterator_traits<RandomAccessIterator>::value_type());
	}

	template<class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		SelfSTL::up(first, last - 1, first, comp);
	}

	template<class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		SelfSTL::pop_heap(first, last, 
			SelfSTL::less < typename SelfSTL::iterator_traits<RandomAccessIterator>::value_type());
	}

	template<class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		SelfSTL::swap(*first, *(last - 1));
		if (last - first >= 2)
		{
			SelfSTL::down(first, last - 2, first, comp);
		}
	}

	template<class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		return SelfSTL::sort_heap(first, last, 
			SelfSTL::less < typename SelfSTL::iterator_traits<RandomAccessIterator>::value_type());
	}

	template<class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		for (auto cur = last; cur != first; --cur)
		{
			SelfSTL::pop_heap(first, cur, comp);
		}
	}

	template<class RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		return SelfSTL::is_heap(first, last, 
			SelfSTL::less<typename SelfSTL::iterator_traits<RandomAccessIterator>::value_type());
	}

	template<class RandomAccessIterator, class Compare>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		const auto range = last - first;
		auto idx = range / 2 - 1;
		for (auto cur = first + range / 2 - 1; cur >= first; --cur, --idx)
		{
			if (*(first + (idx * 2 + 1)) > *cur || 
				((first + (idx * 2 + 2)) <= last && *(first + (idx * 2 + 2)) > *cur))
			{
				return false;
			}

			if (cur == first)
			{
				break;
			}
		}

		return true;
	}

	template<class InputIterator, class UnaryPredicate>
	bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (!pred(*first))
			{
				return false;
			}
		}

		return true;
	}

	template<class InputIterator, class UnaryPredicate>
	bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				return true;
			}
		}
		return false;
	}

	template<class InputIterator, class UnaryPredicate>
	bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				return false;
			}
		}

		return true;
	}

	template<class InputIterator, class Function>
	Function for_each(InputIterator first, InputIterator last, Function fn)
	{
		for (; first != last; ++first)
		{
			fn(*first);
		}
		return fn;
	}

	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; ++first)
		{
			if (*first == value)
			{
				break;
			}
		}

		return first;
	}

	template<class InputIterator, class UnaryPredicate>
	InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				break;
			}
		}

		return first;
	}


	template<class InputIterator, class UnaryPredicate>
	InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (!pred(*first))
			{
				break;
			}
		}

		return first;
	}

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, 
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		if (first2 == last2)
		{
			return last1;
		}

		ForwardIterator1 ret = last1;
		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;
			while (*it1 == *it2)
			{
				++it1;
				++it2;
				if (it2 == last2)
				{
					ret = first1;
					break;
				}
				
				if (it1 == last1)
				{
					return ret;
				}
			}

			++first1;
		}

		return ret;
	}

	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, 
		ForwardIterator2 first2, ForwardIterator2 last2, 
		BinaryPredicate pred)
	{
		if (first2 == last2)
		{
			return last1;
		}

		ForwardIterator1 ret = last1;
		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;
			while (pred(*it1, *it2))
			{
				++it1;
				++it2;
				if (it2 == last2)
				{
					ret = first1;
					break;
				}

				if (it1 == last1)
				{
					return ret;
				}
			}

			++first1;
		}

		return ret;
	}


	/************find_first_of********************/
	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		for (; first1 != last1; ++first1)
		{
			for (auto it = first2; it != last2; ++it)
			{
				if (*first1 == *it)
				{
					return first1;
				}
			}
		}

		return last1;
	}


	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1, 
		ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1)
		{
			for (auto it = first2; it != last2; ++it)
			{
				if (pred(*first1, *it))
				{
					return first1;
				}
			}
		}

		return last1;
	}


	/*************adjacent_find******************/
	template<class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		return SelfSTL::adjacent_find(first, last, equal_to < iterator_traits<typename ForwardIterator>::value_type());
	}

	template<class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (first + 1 != last && pred(*(first), *(first + 1)))
			{
				break;
			}
		}

		return first;
	}


	/**************************adjacent_difference***************************/
	template<class InputIterator, class OutputIterator>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator ret)
	{
		if (first == last)
		{
			return ret;
		}

		*ret = *first;
		return __adjacent_difference(first, last, ret, value_type(first));
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator ret, T*)
	{
		T val = *first;
		while (++first != last)
		{
			//存储第一元素的值，然后存储后继元素的差值，可以有足够信息可以重建输入区间的原始内容
			T tmp = *first;
			*(++ret) = tmp - val;
			val = tmp;
		}

		return ++ret;
	}

	template<class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator ret, BinaryOperation op)
	{
		if (first == last)
		{
			return ret;
		}

		*ret = *first;
		return __adjacent_difference(first, last, ret, value_type(first), op);
	}

	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator ret, T*, BinaryOperation op)
	{
		T value = *first;
		while (++first != last)
		{
			T tmp = *first;
			*(++ret) = op(tmp, value);
			value = tmp;
		}

		return ++ret;
	}


	/**************************inner_product***************************/
	template<class InputIterator1, class InputIterator2, class T>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = init + ((*first1) * (*first2));
		}

		return init;
	}

	template<class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 op1, BinaryOperation2 op2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = op1(init, op2(*first1, *first2));
		}

		return init;
	}


	/**************************accumulate***************************/
	template<class InputIterator, class T>
	T accumulate(InputIterator first, InputIterator last, T init)
	{
		for (; first != last; ++first)
		{
			init = init + *first;
		}
		

		return init;
	}

	template<class InputIterator, class T, class BinaryOperation>
	T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation op)
	{
		for (; first != last; ++first)
		{
			init = op(init, *first);
		}

		return init;
	}



	/**************************partial_sum***************************/
	template<class InputIterator, class OutputIterator>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator ret)
	{
		if (first == last)
		{
			return ret;
		}

		*ret = *first;
		return __partial_sum(first, last, ret, value_type(first));
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator ret, T*)
	{
		T value = *first;
		while (++first != last)
		{
			value = value + (*first);
			*(++ret) = value;
		}

		return ++ret;
	}

	template<class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator ret, BinaryOperation op)
	{
		if (first == last)
		{
			return ret;
		}

		*ret = *first;
		return __partial_sum(first, last, ret, value_type(first), op);
	}

	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator ret, T*, BinaryOperation op)
	{
		T value = *first;
		while (++first != last)
		{
			value = op(value, *first);
			*(++ret) = value;
		}

		return ++ret;
	}

	/*************equal******************/
	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
			{
				return false;
			}
		}

		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first, ++first2)
		{
			if (!pred(*first1, *first2))
			{
				return false;
			}
		}
		
		return true;
	}

	/*************iter_swap******************/
	template<class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
	{
		__iter_swap(a, b, value_type(a));
	}

	template<class ForwardIterator1, class ForwardIterator2, class T>
	void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*)
	{
		T tmp = *a;
		*a = *b;
		*b = tmp;
	}


	/*************lexicographical_compare******************/
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator first2, InputIterator last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
			{
				return true;
			}

			if (*first2 < *first1)
			{
				return false;
			}
		}

		return first1 == last1 && first2 != last2;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator first2, InputIterator last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (comp(*first1, *first2))
			{
				return true;
			}

			if (comp(*first2, *first1))
			{
				return false;
			}
		}

		return first1 == last1 && first2 != last2;
	}

	bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2)
	{
		const size_t len1 = last1 - first1;
		const size_t len2 = last2 - first2;
		const int ret = memcmp(first1, first2, min(len1, len2));
		return ret != 0 ? ret < 0 : len1 < len2;
	}
	/**********Complexity: O(N)**************************/
}