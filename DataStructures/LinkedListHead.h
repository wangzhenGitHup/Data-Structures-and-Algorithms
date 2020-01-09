#pragma once

#include<iostream>

template<class E>
struct Node
{
	Node()
	{
		_next = nullptr;
	}

	Node(E elem)
	{
		_data = elem;
		_next = nullptr;
	}

	E _data;
	Node* _next;
};

template<class T>
class LinkedListHead
{
public:
	LinkedListHead();
	LinkedListHead(T elem);
	LinkedListHead(const LinkedListHead& list);
	LinkedListHead& operator=(const LinkedListHead& list);
	virtual ~LinkedListHead();
	bool IsEmpty() { return _head->_next == nullptr; }
	int GetSize() { return _size; }
	void Insert(int pos, T elem);
	void AddFirst(T elem);
	void AddLast(T elem);
	bool Contains(T elem);
	T Remove(int pos);
	T RemoveFirst();
	T RemoveLast();
	void RemoveElements(T elem);

	T GetData(int pos);
	void PrintInfo()const;
	template<class T> friend std::ostream& operator<<(std::ostream& out, const LinkedListHead<T>& list);

private:
	bool isValied(int pos);
	void copy(Node<T>* pNode);
	Node<T>* RemoveElements(Node<T>* pNode, T elem);

private:
	Node<T>* _head;
	int _size;
};

template<class T>
inline LinkedListHead<T>::LinkedListHead()
{
	_head = new Node<T>();
	_size = 0;
}

template<class T>
inline LinkedListHead<T>::LinkedListHead(T elem)
{
	_head = new Node<T>();
	Node<T>* pNewNode = new Node<T>(elem);
	_head->_next = pNewNode;
	_size++;
}

template<class T>
inline LinkedListHead<T>::LinkedListHead(const LinkedListHead<T> & list)
{
	_head = new Node<T>();
	if (!_head)
	{
		throw "Bad mem!";
	}

	if (_head != nullptr)
	{
		Node<T>* pNode = list._head->_next;
		copy(pNode);
	}
}

template<class T>
LinkedListHead<T>& LinkedListHead<T>::operator=(const LinkedListHead<T>& list)
{
	if (&list == this)
	{
		return *this;
	}

	Node<T>* pNode = list._head->_next;
	_head = new Node<T>();
	if (!_head)
	{
		throw "Bad mem!";
	}

	if (_head != nullptr)
	{
		Node<T>* pNode = list._head->_next;
		copy(pNode);
	}

	return *this;
}

template<class T>
inline LinkedListHead<T>::~LinkedListHead()
{
	Node<T>* pNode = _head->_next;
	while (pNode != nullptr)
	{
		Node<T>* pDelNode = pNode;
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
inline void LinkedListHead<T>::Insert(int pos, T elem)
{
	if (!isValied(pos))
	{
		throw "Index Error!";
		return;
	}

	Node<T>* pNode = _head;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	Node<T>* pNewNode = new Node<T>(elem);
	if (pNewNode != nullptr)
	{
		pNewNode->_next = pNode->_next;
		pNode->_next = pNewNode;
		_size++;
	}
}

template<class T>
inline void LinkedListHead<T>::AddFirst(T elem)
{
	Insert(0, elem);
}

template<class T>
inline void LinkedListHead<T>::AddLast(T elem)
{
	Insert(_size, elem);
}

template<class T>
inline bool LinkedListHead<T>::Contains(T elem)
{
	Node<T>* pNode = _head->_next;
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
inline T LinkedListHead<T>::Remove(int pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw "Remove Index Error";
	}

	Node<T>* pNode = _head;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	T elem;

	Node<T>* pDelNode = pNode->_next;
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
inline T LinkedListHead<T>::RemoveFirst()
{
	return Remove(0);
}

template<class T>
inline T LinkedListHead<T>::RemoveLast()
{
	return Remove(_size - 1);
}

template<class T>
inline Node<T> * LinkedListHead<T>::RemoveElements(Node<T> * pNode, T elem)
{
	if (pNode == nullptr)
	{
		return nullptr;
	}

	pNode->_next = RemoveElements(pNode->_next, elem);
	Node<T>* pDelNode = pNode;
	Node<T>* pTmpNode = pNode->_next;
	bool isEqual = false;
	if (pNode->_data == elem)
	{
		delete pDelNode;
		pDelNode = nullptr;
		isEqual = true;
	}
	return isEqual ? pTmpNode : pNode;
}

template<class T>
inline void LinkedListHead<T>::RemoveElements(T elem)
{
	RemoveElements(_head, elem);
}

template<class T>
inline T LinkedListHead<T>::GetData(int pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw "Index Error";
	}

	Node<T>* pNode = _head->_next;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	return pNode->_data;
}

template<class T>
inline bool LinkedListHead<T>::isValied(int pos)
{
	if (pos < 0 || pos > _size)
	{
		return false;
	}
	return true;
}

template<class T>
inline void LinkedListHead<T>::copy(Node<T> * pNode)
{
	Node<T>* pTailNode = pNode;
	while (pNode != nullptr)
	{
		Node<T>* pNewNode = new Node<T>(pNode->_data);
		if (pNewNode != nullptr)
		{
			if (_head->_next == nullptr)
			{
				pNewNode->_next = _head->_next;
				_head->_next = pNewNode;
				pTailNode = pNewNode;
			}
			else
			{
				pTailNode->_next = pNewNode;
				pTailNode = pNewNode;
			}

			pNode = pNode->_next;
			_size++;
		}
	}
}

template<class T>
inline void LinkedListHead<T>::PrintInfo()const
{
	Node<T>* pNode = _head->_next;
	while (pNode != nullptr)
	{
		std::cout << pNode->_data << " ";
		pNode = pNode->_next;
	}
}

template<class T>
inline std::ostream & operator<<(std::ostream & out, const LinkedListHead<T>& list)
{
	out << "LinkedList: [ ";
	list.PrintInfo();
	out << "]" << std::endl;
	out << "--------------------------" << std::endl;
	return out;
}
