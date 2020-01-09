#pragma once
#include "BinTree.h"

template<class T>
class BSTSet
{
public:
	BSTSet();
	virtual ~BSTSet();
	int GetSize();
	void AddElem(T elem);
	void RemoveElement(T elem);
	bool Contains(T elem);
	bool IsEmpty();
	void ShowElements();

private:
	BinTree<T>* _tree = nullptr;
};

template<class T>
inline BSTSet<T>::BSTSet()
{
	_tree = new BinTree<T>();
}

template<class T>
inline BSTSet<T>::~BSTSet()
{
	delete _tree;
	_tree = nullptr;
}

template<class T>
inline int BSTSet<T>::GetSize()
{
	return _tree->GetSize();
}

template<class T>
inline void BSTSet<T>::AddElem(T elem)
{
	_tree->AddChild(elem);
}

template<class T>
inline void BSTSet<T>::RemoveElement(T elem)
{
	_tree->RemoveElement(elem);
}

template<class T>
inline bool BSTSet<T>::Contains(T elem)
{
	return _tree->Contains(elem);
}

template<class T>
inline bool BSTSet<T>::IsEmpty()
{
	return _tree->IsEmpty();
}

template<class T>
inline void BSTSet<T>::ShowElements()
{
	_tree->PreOrder();
}
