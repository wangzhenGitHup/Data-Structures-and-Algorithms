#pragma once

#include "Construct.h"
#include "Iterator.h"
#include "TypeTraits.h"

namespace SelfSTL
{
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, 
		ForwardIterator result, _true_type);

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, 
		ForwardIterator result, _false_type);

	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, 
		ForwardIterator result)
	{
		typedef typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type isPOD_Type;
		return _uninitialized_copy_aux(first, last, result, isPOD_Type());
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, 
		ForwardIterator result, _true_type)
	{
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - first);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, 
		ForwardIterator result, _false_type)
	{
		int i = 0;
		for (; first != last; ++first, ++i)
		{
			construct((result + i), *first);
		}

		return (result + i);
	}


	template<class ForwardIterator, class T>
	void _unintialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type);

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type);

	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		typedef typename _type_traits<T>::is_POD_type is_POD_type;
		_uninitialized_fill_aux(first, last, value, is_POD_type());
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type)
	{
		fill(first, last, value);
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type)
	{
		for (; first != last; ++first)
		{
			construct(first, value);
		}
	}


	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _true_type); 

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _false_type);

	template<class ForwardIterator, class Size, class T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
	{
		typedef typename _type_traits<T>::is_POD_type is_POD_type;
		return _uninitialized_fill_n_aux(first, n, x, is_POD_type());
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _true_type)
	{
		return fill_n(first, n, x);
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _false_type)
	{
		int i = 0;
		for (; i != n; ++i)
		{
			construct((T*)(first + i), x);
		}

		return (first + i);
	}
}