#pragma once

#include<iostream>

template<class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(T elem);
	LinkedList(const LinkedList& list);
	LinkedList& operator=(const LinkedList& list);
	virtual ~LinkedList();
	bool IsEmpty() { return _head->_next == nullptr; }
	int GetSize() { return _size; }
	void Insert(int pos, T elem);
	void AddFirst(T elem);
	void AddLast(T elem);
	bool Contains(T elem);
	T Remove(int pos);
	T RemoveFirst();
	T RemoveLast();
	T GetData(int pos);
	void PrintInfo()const;
	template<class T> friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list);

private:
	bool isValied(int pos);

private:
	struct Node
	{
		Node()
		{
			_next = nullptr;
		}

		Node(T elem)
		{
			_data = elem;
			_next = nullptr;
		}

		T _data;
		Node* _next;
	};

	Node* _head;
	int _size;
};

template<class T>
inline LinkedList<T>::LinkedList()
{
	_head = new Node();
	_size = 0;
}

template<class T>
inline LinkedList<T>::LinkedList(T elem)
{
	_head = new Node();
	Node* pNewNode = new Node(elem);
	_head->_next = pNewNode;
	_size++;
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList & list)
{
	_head = new Node();
	if (_head != nullptr)
	{
		Node* pNode = list._head;
		while (pNode != nullptr)
		{
			Node* pNewNode = new Node(pNode->_data);
			if (pNewNode != nullptr)
			{
				pNewNode->_next = _head->_next;
				_head->next = pNewNode;
				pNode = pNode->_next;
				_size++;
			}
		}
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	if (&list == this)
	{
		return *this;
	}

	Node* pNode = list._head;
	_head = new Node();
	if (!_head)
	{
		throw "Bad mem!";
	}

	while (pNode != nullptr)
	{
		Node* pNewNode = new Node(pNode->_data);
		if(pNewNode != nullptr)
		{ 
			pNewNode->_next = _head->_next;
			_head->_next = pNewNode;
		}
		pNode = pNode->_next;
	}

	return *this;
}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	Node* pNode = _head->_next;
	while (pNode != nullptr)
	{
		Node* pDelNode = pNode;
		pNode = pNode->_next;

		if (pDelNode != nullptr)
		{
			delete pDelNode;
			pDelNode = nullptr;
		}
	}

	delete _head;
	_head = nullptr;
}

template<class T>
inline void LinkedList<T>::Insert(int pos, T elem)
{
	if (!isValied(pos))
	{
		throw "Index Error!";
		return;
	}

	Node* pNode = _head;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	Node* pNewNode = new Node(elem);
	if (pNewNode != nullptr)
	{
		pNewNode->_next = pNode->_next;
		pNode->_next = pNewNode;
		_size++;
	}
}

template<class T>
inline void LinkedList<T>::AddFirst(T elem)
{
	Insert(0, elem);
}

template<class T>
inline void LinkedList<T>::AddLast(T elem)
{
	Insert(_size, elem);
}

template<class T>
inline bool LinkedList<T>::Contains(T elem)
{
	Node* pNode = _head->_next;
	while (pNode != nullptr)
	{
		if (elem == pNode->_data)
		{
			return true;
		}

		pNode = pNode->_next;
	}
	return false;
}

template<class T>
inline T LinkedList<T>::Remove(int pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw "Remove Index Error";
	}

	Node* pNode = _head;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	T elem;

	Node* pDelNode = pNode->_next;
	if (pDelNode != nullptr)
	{
		elem = pDelNode->_data;
		pNode->_next = pDelNode->_next;

		delete pDelNode;
		pDelNode = nullptr;
		_size--;
	}
	
	return elem;
}

template<class T>
inline T LinkedList<T>::RemoveFirst()
{
	return Remove(0);
}

template<class T>
inline T LinkedList<T>::RemoveLast()
{
	return Remove(_size - 1);
}

template<class T>
inline T LinkedList<T>::GetData(int pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw "Index Error";
	}

	Node* pNode = _head->_next;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	return pNode->_data;
}

template<class T>
inline bool LinkedList<T>::isValied(int pos)
{
	if (pos < 0 || pos > _size)
	{
		return false;
	}
	return true;
}

template<class T>
inline void LinkedList<T>::PrintInfo()const
{
	Node* pNode = _head->_next;
	while (pNode != nullptr)
	{
		std::cout << pNode->_data << " ";
		pNode = pNode->_next;
	}
}

template<class T>
inline std::ostream & operator<<(std::ostream & out, const LinkedList<T>& list)
{
	out << "LinkedList: [ ";
	list.PrintInfo();
	out << "]" << std::endl;
	out << "--------------------------" << std::endl;
	return out;
}
