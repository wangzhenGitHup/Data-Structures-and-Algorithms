#pragma once

#pragma once

#include<iostream>

template<class E>
struct ListNode
{
	ListNode()
	{
		_next = nullptr;
	}

	ListNode(E elem)
	{
		_data = elem;
		_next = nullptr;
	}

	E _data;
	ListNode* _next;
};

template<class T>
class LinkedListCircle
{
public:
	LinkedListCircle();
	LinkedListCircle(T elem);
	LinkedListCircle(const LinkedListCircle& list);
	LinkedListCircle& operator=(const LinkedListCircle& list);
	virtual ~LinkedListCircle();
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
	template<class T> friend std::ostream& operator<<(std::ostream& out, const LinkedListCircle<T>& list);

private:
	bool isValied(int pos);
	void copy(ListNode<T>* pNode, ListNode<T>* pHead);
	ListNode<T>* RemoveElements(ListNode<T>* pNode, T elem);

private:
	ListNode<T>* _head;
	int _size;
};

template<class T>
inline LinkedListCircle<T>::LinkedListCircle()
{
	_head = new ListNode<T>();
	_size = 0;
}

template<class T>
inline LinkedListCircle<T>::LinkedListCircle(T elem)
{
	_head = new ListNode<T>();
	ListNode<T>* pNewNode = new ListNode<T>(elem);
	_head->_next = pNewNode;
	pNewNode->_next = _head;
	_size++;
}

template<class T>
inline LinkedListCircle<T>::LinkedListCircle(const LinkedListCircle<T> & list)
{
	_head = new ListNode<T>();
	if (!_head)
	{
		throw "Bad mem!";
	}

	if (_head != nullptr)
	{
		ListNode<T>* pNode = list._head->_next;
		copy(pNode, list._head);
	}
}

template<class T>
LinkedListCircle<T>& LinkedListCircle<T>::operator=(const LinkedListCircle<T>& list)
{
	if (&list == this)
	{
		return *this;
	}

	ListNode<T>* pNode = list._head->_next;
	_head = new ListNode<T>();
	if (!_head)
	{
		throw "Bad mem!";
	}

	if (_head != nullptr)
	{
		ListNode<T>* pNode = list._head->_next;
		copy(pNode, list._head);
	}

	return *this;
}

template<class T>
inline LinkedListCircle<T>::~LinkedListCircle()
{
	ListNode<T>* pNode = _head->_next;
	while (pNode != _head)
	{
		ListNode<T>* pDelNode = pNode;
		pNode = pNode->_next;

		if (pDelNode != nullptr)
		{
			delete pDelNode;
			pDelNode = nullptr;
		}
		_head->_next = pNode;
	}

	delete _head;
	_head = nullptr;
}

template<class T>
inline void LinkedListCircle<T>::Insert(int pos, T elem)
{
	if (!isValied(pos))
	{
		throw "Index Error!";
		return;
	}

	ListNode<T>* pNode = _head;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	ListNode<T>* pNewNode = new ListNode<T>(elem);
	if (pNewNode != nullptr)
	{
		if (pNode->_next == nullptr)
		{
			pNewNode->_next = pNode;
		}
		else
		{
			pNewNode->_next = pNode->_next;
		}
		
		pNode->_next = pNewNode;
		_size++;
	}
}

template<class T>
inline void LinkedListCircle<T>::AddFirst(T elem)
{
	Insert(0, elem);
}

template<class T>
inline void LinkedListCircle<T>::AddLast(T elem)
{
	Insert(_size, elem);
}

template<class T>
inline bool LinkedListCircle<T>::Contains(T elem)
{
	ListNode<T>* pNode = _head->_next;
	while (pNode != _head)
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
inline T LinkedListCircle<T>::Remove(int pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw "Remove Index Error";
	}

	ListNode<T>* pNode = _head;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	T elem;

	ListNode<T>* pDelNode = pNode->_next;
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
inline T LinkedListCircle<T>::RemoveFirst()
{
	return Remove(0);
}

template<class T>
inline T LinkedListCircle<T>::RemoveLast()
{
	return Remove(_size - 1);
}


template<class T>
inline void LinkedListCircle<T>::RemoveElements(T elem)
{
	RemoveElements(_head->_next, elem);
}

template<class T>
inline T LinkedListCircle<T>::GetData(int pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw "Index Error";
	}

	ListNode<T>* pNode = _head->_next;
	for (int i = 0; i < pos; i++)
	{
		pNode = pNode->_next;
	}

	return pNode->_data;
}

template<class T>
inline bool LinkedListCircle<T>::isValied(int pos)
{
	if (pos < 0 || pos > _size)
	{
		return false;
	}
	return true;
}

template<class T>
inline void LinkedListCircle<T>::copy(ListNode<T> * pNode, ListNode<T>* pHead)
{
	ListNode<T>* pTailNode = pNode;
	while (pNode != pHead)
	{
		ListNode<T>* pNewNode = new ListNode<T>(pNode->_data);
		if (pNewNode != nullptr)
		{
			if (_head->_next == nullptr)
			{
				pNewNode->_next = _head;
				_head->_next = pNewNode;
				pTailNode = pNewNode;
			}
			else
			{
				pNewNode->_next = pTailNode->_next;
				pTailNode->_next = pNewNode;
				pTailNode = pNewNode;
			}

			pNode = pNode->_next;
			_size++;
		}
	}
}

template<class T>
inline ListNode<T> * LinkedListCircle<T>::RemoveElements(ListNode<T> * pNode, T elem)
{
	if (pNode == _head)
	{
		return _head;
	}

	pNode->_next = RemoveElements(pNode->_next, elem);

	ListNode<T>* pDelNode = pNode;
	ListNode<T>* pTmpNode = pNode->_next;
	bool isEqual = false;
	if (pNode->_data == elem)
	{
		_head->_next = pNode;
		delete pDelNode;
		pDelNode = nullptr;
		isEqual = true;
		_head->_next = pTmpNode;
	}
	return isEqual ? pTmpNode : pNode;
}

template<class T>
inline void LinkedListCircle<T>::PrintInfo()const
{
	ListNode<T>* pNode = _head->_next;
	while (pNode != _head)
	{
		std::cout << pNode->_data << " ";
		pNode = pNode->_next;
	}
}

template<class T>
inline std::ostream & operator<<(std::ostream & out, const LinkedListCircle<T>& list)
{
	out << "LinkedList: [ ";
	list.PrintInfo();
	out << "]" << std::endl;
	out << "--------------------------" << std::endl;
	return out;
}

