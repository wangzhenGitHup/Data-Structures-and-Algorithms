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
	T FindMaxValue();
	T ExtractMaxValue();

private:
	int parentIndex(int idx);
	int leftChildIndex(int idx);
	int rightChildIndex(int idx);
	void siftUp(int idx);
	void siftDown(int idx);

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
T MaxHeap<T>::FindMaxValue()
{
	if (_array->GetSize() == 0)
	{
		throw "Heap is empty!";
	}

	return _array->GetData(0);
}

template<class T>
T MaxHeap<T>::ExtractMaxValue()
{
	T maxValue = FindMaxValue();
	_array->Swap(_array->GetData(0), _array->GetData(_array->GetSize() - 1));
	_array->RemoveLast();
	siftDown(0);
	return maxValue;
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

template<class T>
void MaxHeap<T>::siftDown(int idx)
{
	while (leftChildIndex(idx) < _array->GetSize())
	{
		int tmpIdx = leftChildIndex(idx);
		//看下右孩子存不存在且是不是大于左子树
		if (tmpIdx + 1 < _array->GetSize() &&
			_array->GetData(tmpIdx + 1) > _array->GetData(tmpIdx))
		{
			tmpIdx = rightChildIndex(idx);
		}

		//父节点大于左右孩子就满足堆性质了
		if (_array->GetData(idx) >= _array->GetData(tmpIdx))
		{
			break;
		}

		//交换父节点和大于父节点的孩子节点
		_array->Swap(idx, tmpIdx);
		//继续比较
		idx = tmpIdx;
	}
}
