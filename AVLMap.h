#pragma once

#include"AVLTree.h"


template<class K, class V>
class AVLMap
{
public:
	AVLMap();
	~AVLMap();
	void Add(K key, V value);
	void Remove(K key);
	bool Contains(K key);
	V GetValue(K key);
	void Set(K key, V value);
	int GetSize();
	bool IsEmpty();

private:
	AVLTree<K, V>* _tree = nullptr;
};

template<class K, class V>
AVLMap<K, V>::AVLMap()
{
	_tree = new AVLTree<K, V>();
}

template<class K, class V>
AVLMap<K, V>::~AVLMap()
{
	delete _tree;
	_tree = nullptr;
}

template<class K, class V>
void AVLMap<K, V>::Add(K key, V value)
{
	_tree->Add(key, value);
}

template<class K, class V>
void AVLMap<K, V>::Remove(K key)
{
	_tree->Remove(key);
}

template<class K, class V>
bool AVLMap<K, V>::Contains(K key)
{
	return _tree->Contains(key);
}

template<class K, class V>
V AVLMap<K, V>::GetValue(K key)
{
	return _tree->GetValue(key);
}

template<class K, class V>
void AVLMap<K, V>::Set(K key, V value)
{
	_tree->Set(key, value);
}

template<class K, class V>
int AVLMap<K, V>::GetSize()
{
	return _tree->GetSize;
}

template<class K, class V>
bool AVLMap<K, V>::IsEmpty()
{
	return _tree->IsEmpty();
}
