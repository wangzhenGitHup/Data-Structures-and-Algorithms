#pragma once

#include<new>


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
}