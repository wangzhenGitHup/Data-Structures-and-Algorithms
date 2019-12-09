#pragma once

#include "LinkedListHead.h"

template<class T>
class ListSet
{
public:
	ListSet();
	virtual ~ListSet();
	int GetSize();
	void AddElem(T elem);
	void RemoveElement(T elem);
	bool Contains(T elem);
	bool IsEmpty();
	template<class T> friend std::ostream& operator<<(std::ostream& out, const LinkedListHead<T>& list);
	void PrintInfo()const;

private:
	LinkedListHead<T>* _list = nullptr;
};

template<class T>
ListSet<T>::ListSet()
{
	_list = new LinkedListHead<T>();
}

template<class T>
ListSet<T>::~ListSet()
{
	delete _list;
	_list = nullptr;
}

template<class T>
int ListSet<T>::GetSize()
{
	return _list->GetSize();
}

template<class T>
void ListSet<T>::AddElem(T elem)
{
	if (!_list->Contains(elem))
	{
		_list->AddFirst(elem);
	}
}

template<class T>
void ListSet<T>::RemoveElement(T elem)
{
	_list->RemoveElements(elem);
}

template<class T>
bool ListSet<T>::Contains(T elem)
{
	return _list->Contains(elem);
}

template<class T>
bool ListSet<T>::IsEmpty()
{
	return _list->IsEmpty();
}

template<class T>
void ListSet<T>::PrintInfo()const
{
	_list->PrintInfo();
}


template<class T>
std::ostream & operator<<(std::ostream & out, const ListSet<T>& set)
{
	out << "ListSet: [ ";
	set.PrintInfo();
	out << "]" << std::endl;
	out << "--------------------------" << std::endl;
	return out;
}