#pragma once

#include "Alloc.h"
#include <new>

namespace SelfSTL
{
	template<class T>
	class Allocator
	{
	public:
		static T* allocate();
		static T* allocate(size_t n);
		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_t n);
		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void destroy(T* ptr);
		static void destroy(T* first, T* last);

		typedef T         m_value_type;
		typedef T*        m_ptr;
		typedef const T*  m_const_ptr;
		typedef T&        m_ref;
		typedef const T&  m_const_ref;
		typedef size_t    m_size;
		typedef ptrdiff_t m_difference_type;
	};

	template<class T>
	T* Allocator<T>::allocate()
	{
		return static_cast<T*>(Alloc::allocate(sizeof(T)));
	}

	template<class T>
	T * Allocator<T>::allocate(size_t n)
	{
		if (0 == n)
		{
			return nullptr;
		}

		return static_cast<T*>(Alloc::allocate(sizeof(T) * n));
	}

	template<class T>
	void Allocator<T>::deallocate(T * ptr)
	{
		Alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
	}

	template<class T>
	void Allocator<T>::deallocate(T * ptr, size_t n)
	{
		if (0 == n)
		{
			return;
		}

		Alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	template<class T>
	void Allocator<T>::construct(T * ptr)
	{
		new(ptr)T();
	}

	template<class T>
	void Allocator<T>::construct(T * ptr, const T & value)
	{
		new(ptr)T(value);
	}

	template<class T>
	void Allocator<T>::destroy(T * ptr)
	{
		ptr->~T();
	}

	template<class T>
	void Allocator<T>::destroy(T * first, T * last)
	{
		for (; first != last; ++first)
		{
			first->~T();
		}
	}
}