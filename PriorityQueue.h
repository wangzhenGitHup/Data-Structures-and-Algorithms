#pragma once

#include "MaxHeap.h"

template<class T>
class PriorityQueue final
{
public:
	explicit PriorityQueue();
	~PriorityQueue();
	int GetSize();
	bool IsEmpty();
	T GetFront();
	void Enqueue(T elem);
	T Dequeue();

private:
	MaxHeap<T>* _heap = nullptr;
};

template<class T>
PriorityQueue<T>::PriorityQueue()
{
	_heap = new MaxHeap<T>();
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
	delete _heap;
	_heap = nullptr;
}

template<class T>
int PriorityQueue<T>::GetSize()
{
	return _heap->GetSize();
}

template<class T>
bool PriorityQueue<T>::IsEmpty()
{
	return _heap->IsEmpty();
}

template<class T>
T PriorityQueue<T>::GetFront()
{
	return _heap->FindMaxValue();
}

template<class T>
void PriorityQueue<T>::Enqueue(T elem)
{
	_heap->Add(elem);
}

template<class T>
T PriorityQueue<T>::Dequeue()
{
	return _heap->ExtractMaxValue();
}
