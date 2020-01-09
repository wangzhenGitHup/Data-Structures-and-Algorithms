#pragma once

#include <iostream>
#include "MyArray.h"

template<class T>
class ArrayQueue
{
public:
	ArrayQueue();
	ArrayQueue(int capacity);
	ArrayQueue(const ArrayQueue& queue);
	virtual ~ArrayQueue();
	ArrayQueue& operator=(const ArrayQueue& queue);
	void EnQueue(T elem);
	T DeQueue();
	T Front();
	int GetSize()const;
	bool IsEmpty();
	template<class T> friend std::ostream& operator<<(std::ostream& out, const ArrayQueue<T>& queue);

private:
	T GetData(int pos)const;

private:
	MyArray<T> *_array = nullptr;
};


template<class T>
ArrayQueue<T>::~ArrayQueue()
{
	delete _array;
	_array = nullptr;
}

template<class T>
ArrayQueue<T>::ArrayQueue()
{
	_array = new MyArray<T>();
}

template<class T>
ArrayQueue<T>::ArrayQueue(int capacity)
{
	_array = new MyArray<T>(capacity);
}

template<class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& queue)
{
	_array = new MyArray<T>(*queue._array);
}


template<class T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& queue)
{
	_array->operator=(*queue._array);
	return *this;
}

template<class T>
void ArrayQueue<T>::EnQueue(T elem)
{
	_array->AddLast(elem);
}

template<class T>
T ArrayQueue<T>::DeQueue()
{
	return _array->RemoveFirst();
}


template<class T>
T ArrayQueue<T>::Front()
{
	return _array->GetFirstElem();
}


template<class T>
int ArrayQueue<T>::GetSize() const
{
	return _array->GetSize();
}

template<class T>
bool ArrayQueue<T>::IsEmpty()
{
	return _array->IsEmpty();
}

template<class T>
std::ostream& operator<<(std::ostream& out, const ArrayQueue<T>& queue)
{
	out << "[ ";
	for (int i = 0; i < queue.GetSize(); i++)
	{
		out << queue.GetData(i) << " ";
	}
	out << "]" << std::endl;

	out << "--------------------------" << std::endl;

	return out;
}


template<class T>
T ArrayQueue<T>::GetData(int pos)const
{
	return _array->GetData(pos);
}