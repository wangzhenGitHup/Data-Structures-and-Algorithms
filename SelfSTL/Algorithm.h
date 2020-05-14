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


	/*************mismatch******************/
	template<class InputIterator1, class InputIterator2>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}

		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	pair<InputIterator1, InputIterator2>mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1 && pred(*first1, *first2))
		{
			++first1;
			++first2;
		}

		return pair<InputIterator1, InputIterator2>(first1, first2);
	}


	/*************copy******************/
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator ret)
	{
		return __copy_dispatch<InputIterator, OutputIterator>()(first, last, ret);
	}

	template<class InputIterator, class OutputIterator>
	struct __copy_dispatch
	{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator ret)
		{
			return __copy(first, last, ret, iterator_category(first));
		}
	};

	template<class T>
	struct __copy_dispatch<T*, T*>
	{
		T* operator()(T* first, T* last, T* ret)
		{
			typedef typename _type_traits<T>::has_trivial_assignment_operator func;
			return __copy_t(first, last, ret, func());
		}
	};

	template<class T>
	struct __copy_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* ret)
		{
			typedef typename _type_traits<T>::has_trivial_assignment_operator func;
			return _copy_t(first, last, ret, func());
		}
	};


	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator ret, input_iterator_tag)
	{
		for (; first != last; ++first, ++ret)
		{
			*ret = *first;
		}

		return ret;
	}

	template<class RandomAccessIterator, class OutputIterator>
	OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator ret, random_access_iterator_tag)
	{
		return __copy_d(first, last, ret, distance_type(first));
	}

	template<class RandomAccessIterator, class OutputIterator, class Distance>
	OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator ret, Distance*)
	{
		for (Distance n = last - first; n > 0; --n, ++ret, ++first)
		{
			*ret = *first;
		}

		return ret;
	}

	template<class T>
	T* __copy_t(const T* first, const T* last, T* ret, _true_type)
	{
		memmove(ret, first, sizeof(T) * (last - first));
		return ret + (last - first);
	}

	template<class T>
	T* __copy_t(const T* first, const T* last, T* ret, _false_type)
	{
		return __copy_d(first, last, ret, (ptrdiff_t*)0);
	}

	char* copy(const char* first, const char* last, char* ret)
	{
		memmove(ret, first, last - first);
		return ret + (last - first);
	}


	/*************set操作******************/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*ret = *first2;
				++first2;
			}
			else if (*first2 < *first1)
			{
				*ret = *first2;
				++first2;
			}
			else
			{
				*ret = *first1;
				++first1;
				++first2;
			}

			++ret;
		}

		return copy(first2, last2, copy(first1, last1, ret));
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_intersection(InputIterator1 first1, InputIterator last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				++first1;
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				*ret = *first1;
				++first1;
				++first2;
				++ret;
			}

			return ret;
		}
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*ret = *first1;
				++first1;
				++ret;
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}

			return copy(first1, last1, ret);
		}
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*ret = *first1;
				++first1;
				++ret;
			}
			else if (*first2 < *first1)
			{
				*ret = *first2;
				++first2;
				++ret;
			}
			else
			{
				++first1;
				++first2;
			}

			return copy(first2, last2, copy(first1, last1, ret));
		}
	}


	/**********Count**************************/
	template<class InputIterator, class T>
	typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& val)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
		{
			if (*first == val)
			{
				++n;
			}
			return n;
		}
	}

	template<class InputIterator, class T, class Size>
	void count(InputIterator first, InputIterator last, const T& val, Size& n)
	{
		for (; first != last; ++first)
		{
			if (*first == val)
			{
				++n;
			}
		}
	}

	template<class InputIterator, class Predicate>
	typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				++n;
			}
			return n;
		}
	}

	template<class InputIterator, class Predicate, class Size>
	void count_if(InputIterator first, InputIterator last, Predicate pred, Size& n)
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				++n;
			}
		}
	}

	/**********generate**************************/
	template<class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		for (; first != last; ++first)
		{
			*first = gen();
		}
	}

	template<class OutputIterator, class Size, class Generator>
	OutputIterator generate_n(OutputIterator first, Size n, Generator gen)
	{
		for (; n > 0; --n, ++first)
		{
			*first = gen();
		}

		return first;
	}


	/**********includes**************************/
	template<class InputIterator1, class InputIterator2>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1)
			{
				return false;
			}
			else if (*first1 < *first2)
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		return first2 == last2;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first2, *first1))
			{
				return false;
			}
			else if (comp(*first1, *first2))
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		return first2 == last2;
	}


	/**********max_element**************************/
	template<class ForwardIterator>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return first;
		}

		ForwardIterator ret = first;
		while (++first != last)
		{
			if (*ret < *first)
			{
				ret = first;
			}
		}
		return ret;
	}

	template<class ForwardIterator, class Compare>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		if (first == last)
		{
			return first;
		}

		ForwardIterator ret = first;
		while (++first != last)
		{
			if (comp(*ret, *first))
			{
				ret = first;
			}
		}
		return ret;
	}

	/**********min_element**************************/
	template<class ForwardIterator>
	ForwardIterator min_elment(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return first;
		}

		ForwardIterator ret = first;
		while (++first != last)
		{
			if (*first < *ret)
			{
				ret = first;
			}
		}

		return ret;
	}

	template<class ForwardIterator, class Compare>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		if (first == last)
		{
			return first;
		}

		ForwardIterator ret = first;
		while (++first != last)
		{
			if (comp(*first, *ret))
			{
				ret = first;
			}
		}

		return ret;
	}

	/**********merge**************************/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1)
			{
				*ret = *first2;
				++first2;
			}
			else
			{
				*ret = *first1;
				++first1;
			}

			++ret;
		}

		return copy(first2, last2, copy(first1, last1, ret));
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret, Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first2, *first1))
			{
				*ret = *first2;
				++first2;
			}
			else
			{
				*ret = *first1;
				++first1;
			}
			++ret;
		}

		return copy(first2, last2, copy(first1, last1, ret));
	}

	/**********partition**************************/
	template<class BidirectionalIterator, class Predicate>
	BidirectionIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
	{
		while (true)
		{
			while (true)
			{
				if (first == last)
				{
					return first;
				}
				else if (pred(*first))
				{
					++first;
				}
				else
				{
					break;
				}
				
				--last;
			}

			while (true)
			{
				if (first == last)
				{
					return first;
				}
				else if (!pred(*last))
				{
					--last;
				}
				else
				{
					break;
				}
			}

			iter_swap(first, last);
			++first;
		}
	}

	/**********remove**************************/
	template<class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& val)
	{
		first = find(first, last, val);
		ForwardIterator next = first;
		return first == last ? first : remove_copy(++next, last, first, val);
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator ret, const T& val)
	{
		for (; first != last; ++first)
		{
			if (*first != val)
			{
				*ret = *first;
				++ret;
			}
		}

		return ret;
	}

	template<class ForwardIterator, class Predicate>
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
	{
		first = find_if(first, last, pred);
		ForwardIterator next = first;
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}

	template<class InputIterator, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator ret, Predicate pred)
	{
		for (; first != last; ++first)
		{
			if (!pred(*first))
			{
				*ret = *first;
				++ret;
			}
		}
		return ret;
	}

	/**********replace**************************/
	template<class ForwardIterator, class T>
	void replace(ForwardIterator first, ForwardIterator last, const T& oldVal, const T& newVal)
	{
		for (; first != last; ++first)
		{
			if (*first == oldVal)
			{
				*first = newVal;
			}
		}
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator ret, const T& oldVal, const T& newVal)
	{
		for (; first != last; ++first, ++ret)
		{
			*ret = *first == oldVal ? newVal : *first;
		}

		return ret;
	}

	template<class ForwardIterator, class Predicate, class T>
	void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& newVal)
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				*first = newVal;
			}
		}
	}

	template<class Iterator, class OutputIterator, class Predicate, class T>
	OutputIterator replace_copy_if(Iterator first, Iterator last, OutputIterator ret, Predicate pred, const T& newVal)
	{
		for (; first != last; ++first, ++ret)
		{
			*ret = pred(*first) ? newVal : *first;
		}

		return ret;
	}


	/*******************reverse**************************/
	template<class BidirectionalIterator>
	void reverse(BidirectionalIterator first, BidirectionalIterator last)
	{
		__reverse(first, last, iterator_category(first));
	}

	template<class BidirectionalIterator>
	void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag)
	{
		while (true)
		{
			if (first == last || first == --last)
			{
				return;
			}

			iter_swap(first++, last);
		}
	}

	template<class RandomAccessIterator>
	void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		while (first < last)
		{
			iter_swap(first++, --last);
		}
	}

	template<class BidirectionalIterator, class OutputIterator>
	OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator ret)
	{
		while (first != last)
		{
			--last;
			*ret = *last;
			++ret;
		}

		return ret;
	}


	/*******************rotate**************************/
	template<class ForwardIterator>
	void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
	{
		if (first == middle || middle == last)
		{
			return;
		}

		__rotate(first, middle, last, distance_type(first), iterator_category(first));
	}

	template<class ForwardIterator, class Distance>
	void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag)
	{
		for (ForwardIterator it = middle;;)
		{
			iter_swap(first, it);
			++first;
			++it;
			if (first == middle)
			{
				if (it == last)
				{
					return;
				}
			}
			else if (it == last)
			{
				it = middle;
			}
		}
	}

	template<class BidirectionalIterator, class Distance>
	void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, bidirectional_iterator_tag)
	{
		reverse(first, middle);
		reverse(middle, last);
		reverse(first, last);
	}

	template<class RandomAccessIterator, class Distance>
	void __rotate(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Distance*, random_access_iterator_tag)
	{
		Distance n = __gcd(last - first, middle - first);
		while (n--)
		{
			__rotate_cycle(first, last, first + n, middle - first, value_type(first));
		}
	}

	//最大公因子，利用辗转相除法
	template<class EuclideanRingElement>
	EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
	{
		while (n != 0)
		{
			EuclideanRingElement tmp = m % n;
			m = n;
			n = t;
		}
		return m;
	}

	template<class RandomAccessIterator, class Distance, class T>
	void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator initial, Distance shift, T*)
	{
		T value = *initial;
		RandomAccessIterator ptr1 = initial;
		RandomAccessIterator ptr2 = ptr1 + shift;
		while (ptr2 != initial)
		{
			*ptr1 = *ptr2;
			ptr1 = ptr2;
			if (last - ptr2 > shift)
			{
				ptr2 += shift;
			}
			else
			{
				ptr2 = first + (shift - (last - ptr2));
			}
		}

		*ptr1 = value;
	}


	template<class ForwardIterator, class OuputIterator>
	OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator ret)
	{
		return copy(first, middle, copy(middle, last, ret));
	}


	/*******************search**************************/
	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, 
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2));
	}

	template<class ForwardIterator1, class ForwardIterator2, class Distance1, class Distance2>
	ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*)
	{
		Distance1 d1 = 0;
		distance(first1, last1, d1);
		Distance d2 = 0;
		distance(first2, last2, d2);

		if (d1 < d2)
		{
			return last1;
		}

		ForwardIterator1 current1 = first1;
		ForwardIterator2 current2 = first2;

		while (current2 != last2)
		{
			if (*current1 == *current2)
			{
				++current1;
				++current2;
			}
			else
			{
				if (d1 == d2)
				{
					return last1;
				}

				current1 = ++first1;
				current2 = first2;
				--d1;
			}
		}

		return first1;
	}

	template<class ForwardIterator, class Integer, class T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& val)
	{
		if (count <= 0)
		{
			return first;
		}

		first = find(first, last, val);
		while (first != last)
		{
			Integer n = count - 1;
			ForwardIterator i = first;
			++i;
			while (i != last && n != 0 && *i == val)
			{
				++i;
				--n;
			}

			if (n == 0)
			{
				return first;
			}
			first = find(i, last, val);
		}

		return last;
	}

	/*template<class FowardIterator, class Integer, class T, class BinaryPredicate>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, 
		Integer cnt, const T& val, BinaryPredicate pred)
	{
		if (cnt <= 0)
		{
			return first;
		}

		while (first != last)
		{
			if (pred(*first, val))
			{
				break;
			}
			++first;
		}

		while (first != last)
		{
			Integer n = cnt - 1;
			ForwardIterator it = first;
			++it;

			while (it != last && n != 0 && pred(*it, val))
			{
				++it;
				--n;
			}

			if (n == 0)
			{
				return first;
			}

			while (it != last)
			{
				if (pred(*it, val))
				{
					break;
				}
				++it;
			}

			first = it;
		}
		
		return last;
	}*/

	/**********swap_ranges**************************/
	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			iter_swap(first1, first2);
		}
		return first2;
	}


	/**********transform**************************/
	template<class InputIterator, class OutputIterator, class UnaryOperation>
	OutputIterator transform(InputIterator first, InputIterator last, OutputIterator ret, UnaryOperation op)
	{
		for (; first != last; ++first, ++ret)
		{
			*ret = op(*first);
		}

		return ret;
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(InputIterator first, InputIterator last, OutputIterator ret, BinaryOperation op)
	{
		for (; first1 != last1; ++first1, ++first2, ++ret)
		{
			*ret = op(*first1, *first2);
		}

		return ret;
	}



	/**********unique**************************/
	template<class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last)
	{
		first = adjacent_find(first, last);
		return unique_copy(first, last, first);
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator ret)
	{
		if (first == last)
		{
			return ret;
		}

		return __unique_copy(first, last, ret, iterator_category(ret));
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator ret, forward_iterator_tag)
	{
		*ret = *first;
		while (++first != last)
		{
			if (*ret != *first)
			{
				*(++ret) = *first;
			}
		}

		return ++ret;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator ret, output_iterator_tag)
	{
		return __unique_copy(first, last, ret, value_type(first));
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator ret, T*)
	{
		T val = *first;
		*ret = val;
		while (++first != last)
		{
			if (val != *first)
			{
				val = *first;
				*(++ret) = valu;
			}
		}

		return ++ret;
	}
	/**********Complexity: O(N)**************************/
}