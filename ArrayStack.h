#pragma once

#include<iostream>
#include"MyArray.h"

template<class T>
class ArrayStack
{
public:
	ArrayStack();
	ArrayStack(int capacity);
	ArrayStack(const ArrayStack& stack);
	ArrayStack& operator=(const ArrayStack& stack);
	virtual ~ArrayStack();
	void Push(T elem);
	T Pop();
	T Top();
	bool IsEmpty();
	int GetSize()const;
	int GetCapacity();

	template<class T> friend std::ostream& operator<<(std::ostream& out, const ArrayStack<T>& stack);

private:
	T GetData(int pos)const;

private:
	MyArray<T>* _array = nullptr;
};

template<class T>
inline ArrayStack<T>::ArrayStack()
{
	_array = new MyArray<T>();
}

template<class T>
inline ArrayStack<T>::ArrayStack(int capacity)
{
	_array = new MyArray<T>(capacity);
}

template<class T>
inline ArrayStack<T>::ArrayStack(const ArrayStack & stack)
{
	_array = new MyArray<T>(*stack._array);
}

template<class T>
inline ArrayStack<T> & ArrayStack<T>::operator=(const ArrayStack<T> & stack)
{
	_array->operator=(*stack._array);
	return *this;
}

template<class T>
inline ArrayStack<T>::~ArrayStack()
{
	delete _array;
	_array = nullptr;
}

template<class T>
inline void ArrayStack<T>::Push(T elem)
{
	_array->AddLast(elem);
}

template<class T>
inline T ArrayStack<T>::Pop()
{
	return _array->RemoveLast();
}

template<class T>
inline T ArrayStack<T>::Top()
{
	return _array->GetLastElem();
}

template<class T>
inline bool ArrayStack<T>::IsEmpty()
{
	return _array->IsEmpty();
}

template<class T>
inline int ArrayStack<T>::GetSize()const
{
	return _array->GetSize();
}

template<class T>
inline int ArrayStack<T>::GetCapacity()
{
	return _array->GetCapacity();
}

template<class T>
inline T ArrayStack<T>::GetData(int pos)const
{
	return _array->GetData(pos);
}

template<class T>
std::ostream& operator<<(std::ostream& out, const ArrayStack<T>& stack)
{
	out << "[ ";
	for (int i = stack.GetSize() - 1; i >= 0; i--)
	{
		out << stack.GetData(i) << " ";
	}
	out << "]" << std::endl;

	out << "--------------------------" << std::endl;
	return out;
}
