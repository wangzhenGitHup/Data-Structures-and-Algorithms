#pragma once

#include "Iterator.h"

namespace SelfSTL
{
	template<class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__push__heap__aux(first, last, distance_type(first), value_type(first));
	}

	template<class RandomAccessIterator, class Distance, class T>
	void __push__heap__aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
	{
		__push__heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
	}

	template<class RandomAccessIterator, class Distance, class T>
	void __push__heap(RandomAccessIterator first, Distance holeIdx, Distance topIdx, T value)
	{
		Distance parent = (holeIdx - 1) / 2;
		while (holeIdx > topIdx && *(first + parent) < value)
		{
			*(first + holeIdx) = *(first + parent);
			holeIdx = parent;
			parent = (holeIdx - 1) / 2;
		}

		*(first + holeIdx) = value;
	}

	template<class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__pop__heap__aux(first, last, value_type(first));
	}

	template<class RandomAccessIterator, class T>
	void __pop__heap__aux(RandomAccessIterator first, RandomAccessIterator last, T*)
	{
		__pop__heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
	}

	template<class RandomAccessIterator, class T, class Distance>
	void __pop__heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator ret, T value, Distance*)
	{
		*ret = *first;
		__adjust__heap(first, Distance(0), Distance(last - first), value);
	}

	template<class RandomAccessIterator, class Distance, class T>
	void __adjust__heap(RandomAccessIterator first, Distance holeIdx, Distance len, T value)
	{
		Distance topIdx = holeIdx;
		Distance secondChild = 2 * holeIdx + 2;
		while (secondChild < len)
		{
			if (*first + secondChild) < *(first + (secondChild - 1))
			{
				secondChild--;
			}

			*(first + holeIdx) = *(first + secondChild);
			holeIdx = secondChild;
			secondChild = 2 * (secondChild + 1);
		}

		if (secondChild == len)
		{
			*(first + holeIdx) = *(first + (secondChild - 1));
			holeIdx = secondChild - 1;
		}

		__push__heap(first, holeIdx, topIdx, value);
	}

	template<class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		while (last - first > 1)
		{
			pop_heap(first, last--);
		}
	}

	template<class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__make__heap(first, last, value_type(first), distance_type(first));
	}

	template<class RandomAccessIterator, class T, class Distance>
	void __make__heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
	{
		if (last - first < 2)
		{
			return;
		}

		Distance len = last - first;
		Distance parent = (len - 2) / 2;

		while (true)
		{
			__adjust__heap(first, parent, len, T(*(first + parent)));
			if (parent == 0)
			{
				return;
			}
			parent--;
		}
	}
}