#pragma once

#include<iostream>

template<class T>
class MyArray
{
public:
	MyArray();
	MyArray(int capacity);
	virtual ~MyArray();
	void AddLast(T elem);
	void AddFirst(T elem);
	void Insert(T elem, int pos);
	int GetSize() { return _size; }
	int GetCapacity() { return _capacity; }
	bool IsEmpty() { return _size == 0; }
	bool IsFull() { return _size >= _capacity; }
	void PrintArrayElem();
	T GetData(int pos);
	bool Contains(T elem);
	int Find(T elem);
	T Remove(int pos);
	T RemoveFirst();
	T RemoveLast();
	bool RemoveElem(T elem);
	template<class T> friend std::ostream& operator<<(std::ostream& out, const MyArray<T>& arr);

private:
	bool IsVailed(int pos);

private:
	T* _data;
	int _size;
	int _capacity;
};

template<class T>
inline MyArray<T>::MyArray()
{
	_size = 0;
	_capacity = 10;
	_data = new T[_capacity];
}

template<class T>
inline MyArray<T>::MyArray(int capacity)
{
	_size = 0;
	_capacity = capacity;
	_data = new T[_capacity];
}

template<class T>
inline MyArray<T>::~MyArray()
{
	delete[]_data;
	_data = nullptr;
}

template<class T>
inline void MyArray<T>::AddLast(T elem)
{
	Insert(elem, _size);
}

template<class T>
inline void MyArray<T>::AddFirst(T elem)
{
	Insert(elem, 0);
}

template<class T>
inline void MyArray<T>::Insert(T elem, int pos)
{
	if (!IsFull() && IsVailed(pos))
	{
		for (int i = _size - 1; i >= pos; i--)
		{
			_data[i + 1] = _data[i];
		}
		_data[pos] = elem;
		_size++;
	}
}

template<class T>
inline void MyArray<T>::PrintArrayElem()
{
	std::cout << "[ ";
	for (int i = 0; i < _size; i++)
	{
		std::cout << _data[i] << " ";
	}
	std::cout << "]" << std::endl;
}

template<class T>
inline T MyArray<T>::GetData(int pos)
{
	if (!IsVailed)
	{
		throw "Pos Error!";
	}
	return _data[pos];
}

template<class T>
inline bool MyArray<T>::Contains(T elem)
{
	for (int i = 0; i < _size; i++)
	{
		if (elem == _data[i])
		{
			return true;
		}
	}
	return false;
}

template<class T>
inline int MyArray<T>::Find(T elem)
{
	for (int i = 0; i < _size; i++)
	{
		if (elem == _data[i])
		{
			return i + 1;
		}
	}
	return -1;
}

template<class T>
inline T MyArray<T>::Remove(int pos)
{
	if (!IsVailed(pos))
	{
		throw "Index Error!";
	}

	T tmp = _data[pos - 1];
	for (int i = pos - 1; i < _size - 1; i++)
	{
		_data[i] = _data[i + 1];
	}
	_size--;
	_size = (_size >= 0) ? _size : 0;

	return tmp;
}

template<class T>
inline T MyArray<T>::RemoveFirst()
{
	return Remove(0);
}

template<class T>
inline T MyArray<T>::RemoveLast()
{
	return Remove(_size);
}

template<class T>
inline bool MyArray<T>::RemoveElem(T elem)
{
	int idx = Find(elem);
	if (idx < 0)
	{
		return false;
	}
	Remove(idx);
	return false;
}

template<class T>
inline bool MyArray<T>::IsVailed(int pos)
{
	if (pos >= _capacity || pos < 0)
	{
		return false;
	}
	return true;
}


template<class T> 
std::ostream& operator<<(std::ostream& out, const MyArray<T>& arr)
{
	out << "[ ";
	for (int i = 0; i < arr._size; i++)
	{
		out << arr._data[i] << " ";
	}
	out << "]" << std::endl;
	return out;
}