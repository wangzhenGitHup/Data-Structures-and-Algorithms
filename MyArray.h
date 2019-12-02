#pragma once

#include<iostream>

template<class T>
class MyArray
{
public:
	MyArray();
	MyArray(int capacity);
	MyArray(const MyArray& arr);
	MyArray& operator=(const MyArray<T>& arr);
	virtual ~MyArray();
	void AddLast(T elem);
	void AddFirst(T elem);
	void Insert(T elem, int pos);
	int GetSize()const { return _size; }
	int GetCapacity() { return _capacity; }
	bool IsEmpty() { return _size == 0; }
	bool IsFull();
	T GetData(int pos)const;
	bool Contains(T elem);
	int Find(T elem);
	T Remove(int pos);
	T RemoveFirst();
	T RemoveLast();
	bool RemoveElem(T elem);
	template<class T> friend std::ostream& operator<<(std::ostream& out, const MyArray<T>& arr);

	T GetLastElem();
	T GetFirstElem();

private:
	bool IsVailed(int pos)const;
	bool resize(int capacity);
	void PrintArrayInfo()const;
	void copy(const MyArray& arr);
	void copy(T* &tmpData, const MyArray& arr);

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
inline MyArray<T>::MyArray(const MyArray & arr)
{
	_data = new T[arr._capacity];
	if (_data != nullptr)
	{
		copy(arr);
		_size = arr._size;
		_capacity = arr._capacity;
	}
}

template<class T>
MyArray<T> & MyArray<T>::operator=(const MyArray<T>& arr)
{
	if (this == &arr)
	{
		return *this;
	}

	if (_capacity == arr._capacity)
	{
		copy(arr);
		_size = arr._size;

		return *this;
	}

	T* tmpData = new T[arr._capacity];
	if (tmpData != nullptr)
	{
		copy(tmpData, arr);
		_size = arr._size;
		_capacity = arr._capacity;
		delete[]_data;
		_data = tmpData;
	}

	return *this;
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
	//O(1)
	Insert(elem, _size);
}

template<class T>
inline void MyArray<T>::AddFirst(T elem)
{
	//O(n)
	Insert(elem, 0);
}

template<class T>
inline void MyArray<T>::Insert(T elem, int pos)
{
	//O(n / 2) = O(n)
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
inline bool MyArray<T>::IsFull()
{
	if (_size >= _capacity)
	{
		if (resize(_capacity << 1))
		{
			return false;
		}

		return true;
	}
	return false;
}

template<class T>
inline void MyArray<T>::PrintArrayInfo() const
{
	std::cout << "ArrayInfo: size = " << _size << ", capacity = " << _capacity << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
}

template<class T>
inline void MyArray<T>::copy(const MyArray & arr)
{
	//O(n)
	for (int i = 0; i < arr._size; i++)
	{
		_data[i] = arr._data[i];
	}
}

template<class T>
inline void MyArray<T>::copy(T * &tmpData, const MyArray & arr)
{
	//O(n)
	if (tmpData != nullptr)
	{
		for (int i = 0; i < arr._size; i++)
		{
			tmpData[i] = arr._data[i];
		}
	}
}

template<class T>
inline T MyArray<T>::GetData(int pos)const
{
	//O(1)
	if (!IsVailed(pos))
	{
		throw "Pos Error!";
	}
	return _data[pos];
}

template<class T>
inline bool MyArray<T>::Contains(T elem)
{
	//O(n)
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
	//O(n)
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
	//O(n)
	if (!IsVailed(pos))
	{
		throw "Index Error!";
	}

	//∑¿÷π∏¥‘”∂»’µ¥
	if (_size <= (_capacity >> 2) &&
		(_capacity >> 1) > 0)
	{
		resize(_capacity >> 1);
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
	return Remove(1);
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
inline T MyArray<T>::GetLastElem()
{
	return GetData(_size - 1);
}

template<class T>
inline T MyArray<T>::GetFirstElem()
{
	return GetData(0);
}

template<class T>
inline bool MyArray<T>::IsVailed(int pos)const
{
	if (pos >= _capacity || pos < 0)
	{
		return false;
	}
	return true;
}

template<class T>
inline bool MyArray<T>::resize(int capacity)
{
	T* tmpData = new T[capacity];
	if (tmpData != nullptr)
	{
		for (int i = 0; i < _size; i++)
		{
			tmpData[i] = _data[i];
		}

		delete[]_data;
		_data = tmpData;
		_capacity = capacity;
		return true;
	}

	return false;
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

	arr.PrintArrayInfo();
	return out;
}