#pragma once

#include<new>
#include "TypeTraits.h"

namespace SelfSTL{
	template<class T1, class T2>
	void construct(T1* ptr1, T2& value)
	{
		new(ptr1)(value);
	}

	template<class T>
	void destroy(T* ptr)
	{
		ptr->~T();
	}

	template<class ForwardIterator>
	void _destroy(ForwardIterator first, ForwardIterator last, _true_type)
	{

	}

	template<class ForwardIterator>
	void _destroy(ForwardIterator first, ForwardIterator last, _false_type)
	{
		for (; first != last; ++first)
		{
			destroy(&(*first));
		}
	}

	template<class ForwardIterator>
	void destroy(ForwardIterator first, ForwardIterator last)
	{
		typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
		_destroy(first, last, is_POD_type());
	}
}