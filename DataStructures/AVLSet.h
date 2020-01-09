#pragma once

#include"AVLTree.h"

template<class K>
class AVLSet
{
public:
	AVLSet();
	virtual ~AVLSet();
	int GetSize();
	void Add(K key);
	void Remove(K key);
	bool Contains(K key);
	bool IsEmpty();

private:
	AVLTree<K, int>* _tree = nullptr;
};

template<class K>
AVLSet<K>::AVLSet()
{
	_tree = new AVLTree<K, int>();
}

template<class K>
AVLSet<K>::~AVLSet()
{
	delete _tree;
	_tree = nullptr;
}

template<class K>
int AVLSet<K>::GetSize()
{
	return _tree->GetSize();
}

template<class K>
void AVLSet<K>::Add(K key)
{
	_tree->Add(key, 0);
}

template<class K>
void AVLSet<K>::Remove(K key)
{
	_tree->Remove(key);
}

template<class K>
bool AVLSet<K>::Contains(K key)
{
	return _tree->Contains(key);
}

template<class K>
bool AVLSet<K>::IsEmpty()
{
	return _tree->IsEmpty();
}
