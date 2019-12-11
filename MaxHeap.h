#pragma once

#include "MyArray.h"

template<class T>
class MaxHeap
{
public:
	MaxHeap();
	MaxHeap(int capacity);
	virtual ~MaxHeap();
	int GetSize();
	bool IsEmpty();
	void Add(T elem);

private:
	int parentIndex(int idx);
	int leftChildIndex(int idx);
	int rightChildIndex(int idx);
	void siftUp(int idx);

private:
	MyArray<T>* _array = nullptr;
};

template<class T>
MaxHeap<T>::MaxHeap()
{
	_array = new MyArray<T>();
}

template<class T>
MaxHeap<T>::MaxHeap(int capacity)
{
	_array = new MyArray<T>(capacity);
}

template<class T>
MaxHeap<T>::~MaxHeap()
{
	delete _array;
	_array = nullptr;
}

template<class T>
int MaxHeap<T>::GetSize()
{
	return _array->GetSize();
}

template<class T>
bool MaxHeap<T>::IsEmpty()
{
	return _array->IsEmpty();
}

template<class T>
void MaxHeap<T>::Add(T elem)
{
	_array->AddLast(elem);
	siftUp(_array->GetSize() - 1);
}

template<class T>
int MaxHeap<T>::parentIndex(int idx)
{
	if (idx == 0)
	{
		throw "Index is Zero!";
	}

	return (idx - 1) >> 1;
}

template<class T>
int MaxHeap<T>::leftChildIndex(int idx)
{
	return (idx << 1) + 1;
}

template<class T>
int MaxHeap<T>::rightChildIndex(int idx)
{
	return (idx << 1) + 2;
}

template<class T>
void MaxHeap<T>::siftUp(int idx)
{
	while (idx > 0 && 
		_array->GetData(parentIndex(idx)) < _array->GetData(idx))
	{
		_array->Swap(idx, parentIndex(idx));
		idx = parentIndex(idx);
	}
}
