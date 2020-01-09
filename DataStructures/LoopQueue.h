#pragma once

#include<iostream>

template<class T>
class LoopQueue
{
public:
	LoopQueue();
	LoopQueue(int capacity);
	LoopQueue(const LoopQueue& queue);
	virtual ~LoopQueue();
	LoopQueue& operator=(const LoopQueue& queue);
	void Enqueue(T elem);
	T Dequeue();
	int GetSize() { return _size; }
	int GetCapacity() { return _capacity; }
	bool IsEmpty() { return _front == _tail; }
	bool IsFull() { return (_tail + 1) % _capacity == _front; }
	template<class T> friend std::ostream& operator<<(std::ostream& out, const LoopQueue<T>& queue);

private:
	void copy(const LoopQueue& queue);
	void copy(const T* &tmpData, const LoopQueue& queue);
	void resize(int capacity);

private:
	T* _data;
	int _front;
	int _tail;
	int _size;
	int _capacity;
	const int DEFAULT_CAPACITY = 10;
};

template<class T>
inline LoopQueue<T>::LoopQueue()
{
	_data = new T[DEFAULT_CAPACITY + 1];
	_capacity = DEFAULT_CAPACITY;
	_size = 0;
	_front = _tail = 0;
}

template<class T>
inline LoopQueue<T>::LoopQueue(int capacity)
{
	_capacity = capacity;
	_size = 0;
	_data = new T[capacity + 1];
	_front = _tail = 0;
}

template<class T>
inline LoopQueue<T>::LoopQueue(const LoopQueue & queue)
{
	_capacity = queue._capacity;
	_size = queue._size;
	_data = new T[_capacity + 1];
	_front = _tail = 0;
	copy(queue);
}

template<class T>
inline LoopQueue<T>::~LoopQueue()
{
	delete[]_data;
	_data = nullptr;
}

template<class T>
inline LoopQueue<T> & LoopQueue<T>::operator=(const LoopQueue<T> & queue)
{
	if (&queue == this)
	{
		return *this;
	}

	if (queue._capacity == _capacity)
	{
		copy(queue);
		_size = queue._size;
		_front = _tail = 0;
		return *this;
	}

	T* tmpData = new T[queue._capacity + 1];
	if (tmpData != nullptr)
	{
		copy(tmpData, queue);
		_size = queue._size;
		_capacity = queue._capacity;
		_front = _tail = 0;
		delete[] _data;
		_data = tmpData;
	}

	return *this;
}

template<class T>
inline void LoopQueue<T>::Enqueue(T elem)
{
	if (IsFull())
	{
		resize(_capacity << 1);
	}
	_data[_tail] = elem;
	_tail = (_tail + 1) % _capacity;
	_size++;
}

template<class T>
inline T LoopQueue<T>::Dequeue()
{
	if (IsEmpty())
	{
		throw "Queue Empty!";
	}

	T elem = _data[_front];
	_front = (_front + 1) % _capacity;
	_size--;

	if (_size <= (_capacity >> 2) && (_capacity >> 1) > 0)
	{
		resize(_capacity >> 1);
	}
	return elem;
}

template<class T>
inline void LoopQueue<T>::copy(const LoopQueue & queue)
{
	for (int i = queue._front; i != queue._tail; 
		i = (i + 1) % queue._capacity)
	{
		_data[i] = queue._data[i];
	}
}

template<class T>
inline void LoopQueue<T>::copy(const T *& tmpData, const LoopQueue & queue)
{
	if (tmpData != nullptr)
	{
		for (int i = queue._front; i != queue._tail; 
			i = (i + 1) % queue._capacity)
		{
			tmpData[i] = queue._data[i];
		}
	}
}

template<class T>
inline void LoopQueue<T>::resize(int capacity)
{
	T* tmpData = new T[capacity + 1];
	if (tmpData != nullptr)
	{
		for (int i = 0; i < _size; i++)
		{
			tmpData[i] = _data[(_front + i) % _capacity];
		}
		_capacity = capacity;
		delete[] _data;
		_data = tmpData;
		_front = 0;
		_tail = _size;
	}
}

template<class T>
inline std::ostream & operator<<(std::ostream & out, const LoopQueue<T> & queue)
{
	out << "LoopQueue: [ ";
	for (int i = queue._front; i != queue._tail; i = (i + 1) % queue._capacity)
	{
		out << queue._data[i] << " ";
	}
	out << "]" << std::endl;
	out << "------------------------------------------" << std::endl;
	return out;
}
