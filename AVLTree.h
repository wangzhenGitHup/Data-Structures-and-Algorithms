#pragma once
#include <iostream>
#include "ArrayStack.h"
#include "MyArray.h"

template<class K, class V>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void Add(K key, V value);
	void Remove(K key);
	bool Contains(K key);
	V GetValue(K key);
	void Set(K key, V value);
	int GetSize() { return _size; }
	bool IsEmpty() { return _size == 0; }
	bool IsBST();
	bool IsBalance();

private:
	struct TreeNode
	{
		TreeNode()
		{
			_key = K();
			_value = V();
			_leftChild = _rightChild = nullptr;
			_height = 0;
		}
		TreeNode(K key, V value)
		{
			_key = key;
			_value = value;
			_leftChild = _rightChild = nullptr;
			_height = 1;
		}

		K _key;
		V _value;
		TreeNode* _leftChild;
		TreeNode* _rightChild;
		int _height;
	};

	TreeNode* addChild(TreeNode* pRoot, K key, V value)
	{
		if (pRoot == nullptr)
		{
			_size++;
			TreeNode* pNewNode = new TreeNode(key, value);
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

		int leftH = getHeight(pRoot->_leftChild);
		int rightH = getHeight(pRoot->_rightChild);
		pRoot->_height = 1 + (leftH > rightH ? leftH : rightH);

		//看下是否平衡

		int balance = getBalanceFactor(pRoot);
		if (balance > 1)
		{

		}
		return pRoot;
	}

	bool contains(TreeNode* pRoot, K key)
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

	TreeNode* getNode(TreeNode* pRoot, K key)
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

	TreeNode* remove(TreeNode* pRoot, K key)
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
			TreeNode* pNode = pRoot->_rightChild;
			delete pRoot;
			pRoot = nullptr;
			_size--;
			return pNode;
		}

		if (pRoot->_rightChild == nullptr)
		{
			TreeNode* pNode = pRoot->_leftChild;
			delete pRoot;
			pRoot = nullptr;
			_size--;
			return pNode;
		}

		TreeNode* pMinNode = findMinNode(pRoot->_rightChild);
		pRoot->_key = pMinNode->_key;
		pRoot->_value = pMinNode->_value;
		delete pMinNode;
		pMinNode = nullptr;
		_size--;
		return nullptr;
	}

	void remove(TreeNode* pRoot)
	{
		if (pRoot == nullptr)
		{
			return;
		}

		TreeNode* pNode = nullptr;
		ArrayStack<TreeNode*> stack;
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

	TreeNode* findMinNode(TreeNode* pRoot)
	{
		if (pRoot == nullptr)
		{
			return nullptr;
		}

		if (pRoot->_leftChild == nullptr)
		{
			return pRoot;
		}

		return findMinNode(pRoot->_leftChild);
	}

	int getHeight(TreeNode* pNode)
	{
		if (pNode == nullptr)
		{
			return 0;
		}
		return pNode->_height;
	}

	int getBalanceFactor(TreeNode* pNode)
	{
		if (pNode == nullptr)
		{
			return 0;
		}

		return getHeight(pNode->_leftChild) - getHeight(pNode->_rightChild);
	}

	void inOrder(TreeNode* pNode, MyArray<K>& list)
	{
		if (pNode == nullptr)
		{
			return;
		}

		inOrder(pNode->_leftChild, list);
		list.AddLast(pNode->_key);
		inOrder(pNode->_rightChild, list);
	}

	bool checkBalance(TreeNode* pNode)
	{
		if (pNode == nullptr)
		{
			return true;
		}

		int balance = getBalanceFactor(pNode);
		if (balance > 1)
		{
			return false;
		}

		return checkBalance(pNode->_leftChild) && checkBalance(pNode->_rightChild);
	}

	TreeNode* rightRotate(TreeNode* pNode)
	{
		TreeNode* xNode = pNode->_leftChild;
		TreeNode* xRNode = xNode->_rightChild;
		xRNode->_rightChild = pNode;
		pNode->_leftChild = xRNode;

		int leftH = getHeight(pNode->_leftChild);
		int rightH = getHeight(pNode->_rightChild);
		pNode->_height = leftH > rightH ? (leftH + 1) : (rightH + 1);

		leftH = getHeight(xNode->_leftChild);
		rightH = getHeight(xNode->_rightChild);
		xNode->_height = leftH > rightH ? (leftH + 1) : (rightH + 1);

		return xNode;
	}

private:
	TreeNode* _root = nullptr;
	int _size;
};

template<class K, class V>
AVLTree<K, V>::AVLTree()
{

}

template<class K, class V>
AVLTree<K, V>::~AVLTree()
{
	remove(_root);
}

template<class K, class V>
void AVLTree<K, V>::Add(K key, V value)
{
	_root = addChild(_root, key, value);
}

template<class K, class V>
void AVLTree<K, V>::Remove(K key)
{

}

template<class K, class V>
bool AVLTree<K, V>::Contains(K key)
{
	return contains(_root, key);
}

template<class K, class V>
V AVLTree<K, V>::GetValue(K key)
{
	TreeNode* pNode = getNode(_root, key);
	if (pNode != nullptr)
	{
		return pNode->_value;
	}

	return V();
}

template<class K, class V>
void AVLTree<K, V>::Set(K key, V value)
{
	TreeNode* pNode = getNode(_root, key);
	if (pNode == nullptr)
	{
		throw "Without this Key!";
	}
	pNode->_value = key;
}

template<class K, class V>
bool AVLTree<K, V>::IsBST()
{
	MyArray<K> list = MyArray<K>();
	inOrder(_root, list);
	int len = list.GetSize();
	for (int i = 1; i < len; i++)
	{
		if (list.GetData(i - 1) > list.GetData(i))
		{
			return false;
		}
	}
	return true;
}

template<class K, class V>
bool AVLTree<K, V>::IsBalance()
{
	return checkBalance(_root);
}
