#pragma once
#include <iostream>
#include "ArrayStack.h"

template<class K, class V>
class BSTMap
{
public:
	BSTMap();
	virtual ~BSTMap();
	void Add(K key, V value);
	void Remove(K key);
	bool Contains(K key);
	V GetValue(K key);
	void Set(K key, V value);
	int GetSize(){ return _size; }
	bool IsEmpty(){ return _size == 0; }

private:
	struct BSTMapNode
	{
		BSTMapNode()
		{
			_key = K();
			_value = V();
			_leftChild = _rightChild = nullptr;
		}
		BSTMapNode(K key, V value)
		{
			_key = key;
			_value = value;
			_leftChild = _rightChild = nullptr;
		}

		K _key;
		V _value;
		BSTMapNode* _leftChild;
		BSTMapNode* _rightChild;
	};

	BSTMapNode* addChild(BSTMapNode* pRoot, K key, V value)
	{
		if (pRoot == nullptr)
		{
			_size++;
			BSTMapNode* pNewNode = new BSTMapNode(key, value);
			return pNewNode;
		}

		if (key < pRoot->_key)
		{
			pRoot->_leftChild = addChild(pRoot->_leftChild, key, value);
		}
		else if (key > pRoot->_key)
		{
			pRoot->_rightChild = addChild(pRoot->_rightChild, key, value);
		}

		return pRoot;
	}

	bool contains(BSTMapNode* pRoot, K key)
	{
		if (pRoot == nullptr)
		{
			return false;
		}

		if (pRoot->_key == key)
		{
			return true;
		}

		if (key < pRoot->_key)
		{
			return contains(pRoot->_leftChild, key);
		}

		return contains(pRoot->_rightChild, key);
	}

	BSTMapNode* getNode(BSTMapNode* pRoot, K key)
	{
		if (pRoot == nullptr)
		{
			return nullptr;
		}

		if (pRoot->_key == key)
		{
			return pRoot;
		}

		if (key < pRoot->_key)
		{
			return getNode(pRoot->_leftChild, key);
		}

		return getNode(pRoot->_rightChild, key);
	}

	BSTMapNode* remove(BSTMapNode* pRoot, K key)
	{
		if (pRoot == nullptr)
		{
			return nullptr;
		}

		if (key < pRoot->_key)
		{
			pRoot->_leftChild = remove(pRoot->_leftChild, key);
			return pRoot;
		}

		if (key > pRoot->_key)
		{
			pRoot->_rightChild = remove(pRoot->_rightChild, key);
			return pRoot;
		}

		if (pRoot->_leftChild == nullptr)
		{
			BSTMapNode* pNode = pRoot->_rightChild;
			delete pRoot;
			pRoot = nullptr;
			_size--;
			return pNode;
		}

		if (pRoot->_rightChild == nullptr)
		{
			BSTMapNode* pNode = pRoot->_leftChild;
			delete pRoot;
			pRoot = nullptr;
			_size--;
			return pNode;
		}

		BSTMapNode* pMinNode = findMinNode(pRoot->_rightChild);
		pRoot->_key = pMinNode->_key;
		pRoot->_value = pMinNode->_value;
		delete pMinNode;
		pMinNode = nullptr;
		_size--;
		return nullptr;
	}

	void remove(BSTMapNode* pRoot)
	{
		if (pRoot == nullptr)
		{
			return;
		}

		BSTMapNode* pNode = nullptr;
		ArrayStack<BSTMapNode*> stack;
		stack.Push(pRoot);

		while (!stack.IsEmpty())
		{
			pNode = stack.Pop();
			if (pNode->_rightChild != nullptr)
			{
				stack.Push(pNode->_rightChild);
			}

			if (pNode->_leftChild != nullptr)
			{
				stack.Push(pNode->_leftChild);
			}
			delete pNode;
			pNode = nullptr;
		}
	}

	BSTMapNode* findMinNode(BSTMapNode* pRoot)
	{
		if (pRoot ==  nullptr)
		{
			return nullptr;
		}

		if (pRoot->_leftChild == nullptr)
		{
			return pRoot;
		}

		return findMinNode(pRoot->_leftChild);
	}

private:
	BSTMapNode* _root = nullptr;
	int _size;
};

template<class K, class V>
BSTMap<K, V>::BSTMap()
{

}

template<class K, class V>
BSTMap<K, V>::~BSTMap()
{
	remove(_root);
}

template<class K, class V>
void BSTMap<K, V>::Add(K key, V value)
{
	_root = addChild(_root, key, value);
}

template<class K, class V>
void BSTMap<K, V>::Remove(K key)
{

}

template<class K, class V>
bool BSTMap<K, V>::Contains(K key)
{
	return contains(_root, key);
}

template<class K, class V>
V BSTMap<K, V>::GetValue(K key)
{
	BSTMapNode* pNode = getNode(_root, key);
	if (pNode != nullptr)
	{
		return pNode->_value;
	}

	return V();
}

template<class K, class V>
void BSTMap<K, V>::Set(K key, V value)
{
	BSTMapNode* pNode = getNode(_root, key);
	if (pNode == nullptr)
	{
		throw "Without this Key!";
	}
	pNode->_value = key;
}