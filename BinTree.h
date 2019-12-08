#pragma once
#include "ArrayStack.h"
#include "ArrayQueue.h"

template<typename E>
struct TreeNode
{
	TreeNode()
	{
		_leftChild = _rightChild = nullptr;
	}

	TreeNode(E data)
	{
		_data = data;
		_leftChild = _rightChild = nullptr;
	}
	
	E _data;
	TreeNode* _leftChild;
	TreeNode* _rightChild;
};

template<class T>
class BinTree
{
public:
	BinTree();
	BinTree(T elem);
	BinTree(const BinTree& tree);
	BinTree& operator=(const BinTree& tree);
	virtual ~BinTree();
	void AddChild(T elem);
	bool Contains(T elem);
	void PreOrder();
	void PreOrderNR();
	void InOrder();
	void InOrderNR();
	void PostOrder();
	void PostOrderNR();
	void LevelOrder();
	T FindMinNode();
	T FindMaxNode();
	void RemoveMinNode();
	void RemoveMaxNode();
	int GetTreeHeight();
	void RemoveElement(T elem);

private:
	TreeNode<T>* addChild(TreeNode<T>* pRoot, T elem);
	void copy(const TreeNode<T>* pRoot);
	bool contains(const TreeNode<T>* pRoot, T elem);
	void preOrder(TreeNode<T>* pRoot);
	void inOrder(TreeNode<T>* pRoot);
	void postOrder(TreeNode<T>* pRoot);
	TreeNode<T>* findMinNode(TreeNode<T>* pRoot);
	TreeNode<T>* findMaxNode(TreeNode<T>* pRoot);
	TreeNode<T>* removeMinNode(TreeNode<T>* pRoot);
	TreeNode<T>* removeMaxNode(TreeNode<T>* pRoot);
	int getHeight(TreeNode<T>* pRoot);
	TreeNode<T>* removeElement(TreeNode<T>* pRoot, T elem);

private:
	TreeNode<T>* _root = nullptr;
};

template<class T>
inline BinTree<T>::BinTree()
{
}

template<class T>
inline BinTree<T>::BinTree(T elem)
{
	AddChild(elem);
}

template<class T>
inline BinTree<T>::BinTree(const BinTree & tree)
{
	copy(tree->_root);
}

template<class T>
inline BinTree<T> & BinTree<T>::operator=(const BinTree<T> & tree)
{
	if (&tree == this)
	{
		return *this;
	}

	copy(tree->_root);
	return *this;
}

template<class T>
inline BinTree<T>::~BinTree()
{
}

template<class T>
inline void BinTree<T>::AddChild(T elem)
{
	_root = addChild(_root, elem);
}

template<class T>
inline bool BinTree<T>::Contains(T elem)
{
	return contains(_root, elem);
}

template<class T>
inline void BinTree<T>::PreOrder()
{
	preOrder(_root);
	std::cout << std::endl;
}

template<class T>
inline void BinTree<T>::PreOrderNR()
{
	if (_root == nullptr)
	{
		return;
	}

	TreeNode<T>* pNode = nullptr;
	ArrayStack<TreeNode<T>*>stack;
	stack.Push(_root);

	while (!stack.IsEmpty())
	{
		pNode = stack.Pop();
		std::cout << pNode->_data << " ";
		
		if (pNode->_rightChild != nullptr)
		{
			stack.Push(pNode->_rightChild);
		}

		if (pNode->_leftChild != nullptr)
		{
			stack.Push(pNode->_leftChild);
		}
	}

	std::cout << std::endl;
}

template<class T>
inline void BinTree<T>::InOrder()
{
	inOrder(_root);
	std::cout << std::endl;
}

template<class T>
inline void BinTree<T>::InOrderNR()
{
	if (_root == nullptr)
	{
		return;
	}

	ArrayStack<TreeNode<T>*> stack;
	stack.Push(_root);

	TreeNode<T>* pNode = _root->_leftChild;

	while (!stack.IsEmpty() || pNode != nullptr)
	{
		while (pNode != nullptr)
		{
			stack.Push(pNode);
			pNode = pNode->_leftChild;
		}
		
		pNode = stack.Pop();
		std::cout << pNode->_data << " ";
		pNode = pNode->_rightChild;
	}

	std::cout << std::endl;
}

template<class T>
inline void BinTree<T>::PostOrder()
{
	postOrder(_root);
	std::cout << std::endl;
}

template<class T>
inline void BinTree<T>::PostOrderNR()
{
	if (_root == nullptr)
	{
		return;
	}

	TreeNode<T>* pNode = _root;
}

template<class T>
inline void BinTree<T>::LevelOrder()
{
	if (_root == nullptr)
	{
		return;
	}

	TreeNode<T>* pNode = nullptr;
	ArrayQueue<TreeNode<T>*> queue;
	queue.EnQueue(_root);

	while (!queue.IsEmpty())
	{
		pNode = queue.DeQueue();
		std::cout << pNode->_data << " ";
		if (pNode->_leftChild != nullptr)
		{
			queue.EnQueue(pNode->_leftChild);
		}

		if (pNode->_rightChild != nullptr)
		{
			queue.EnQueue(pNode->_rightChild);
		}
	}

	std::cout << std::endl;
}

template<class T>
inline T BinTree<T>::FindMinNode()
{
	TreeNode<T>*pNode = findMinNode(_root);
	if (pNode != nullptr)
	{
		return pNode->_data;
	}

	throw "BinTree Error!";
}

template<class T>
inline T BinTree<T>::FindMaxNode()
{
	TreeNode<T>*pNode = findMaxNode(_root);
	if (pNode != nullptr)
	{
		return pNode->_data;
	}

	throw "BinTree Error!";
}

template<class T>
inline void BinTree<T>::RemoveMinNode()
{
	removeMinNode(_root);
}

template<class T>
inline void BinTree<T>::RemoveMaxNode()
{
	removeMaxNode(_root);
}

template<class T>
inline int BinTree<T>::GetTreeHeight()
{
	return getHeight(_root);
}

template<class T>
inline void BinTree<T>::RemoveElement(T elem)
{
	if (_root == nullptr)
	{
		return;
	}

	_root = removeElement(_root, elem);
}

template<class T>
inline TreeNode<T>*  BinTree<T>::addChild(TreeNode<T>* pRoot, T elem)
{
	if (pRoot == nullptr)
	{
		return new TreeNode<T>(elem);
	}
	
	if (elem < pRoot->_data)
	{
		pRoot->_leftChild = addChild(pRoot->_leftChild, elem);
	}
	else if (elem > pRoot->_data)
	{
		pRoot->_rightChild = addChild(pRoot->_rightChild, elem);
	}

	return pRoot;
}

template<class T>
inline void BinTree<T>::copy(const TreeNode<T>* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	AddChild(pRoot->_data);
	copy(pRoot->_leftChild);
	copy(pRoot->_rightChild);
}

template<class T>
inline bool BinTree<T>::contains(const TreeNode<T>* pRoot, T elem)
{
	if (pRoot == nullptr)
	{
		return false;
	}

	if (elem == pRoot->_data)
	{
		return true;
	}

	if (elem < pRoot->_data)
	{
		return contains(pRoot->_leftChild, elem);
	}

	if (elem > pRoot->_data)
	{
		return contains(pRoot->_rightChild, elem);
	}
}

template<class T>
inline void BinTree<T>::preOrder(TreeNode<T>* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	std::cout << pRoot->_data << " ";
	preOrder(pRoot->_leftChild);
	preOrder(pRoot->_rightChild);
}

template<class T>
inline void BinTree<T>::inOrder(TreeNode<T>* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	inOrder(pRoot->_leftChild);
	std::cout << pRoot->_data << " ";
	inOrder(pRoot->_rightChild);
}

template<class T>
inline void BinTree<T>::postOrder(TreeNode<T>* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}
	postOrder(pRoot->_leftChild);
	postOrder(pRoot->_rightChild);
	std::cout << pRoot->_data << " ";
}

template<class T>
inline TreeNode<T>* BinTree<T>::findMinNode(TreeNode<T>* pRoot)
{
	if (pRoot->_leftChild == nullptr)
	{
		return pRoot;
	}

	return findMinNode(pRoot->_leftChild);
}

template<class T>
inline TreeNode<T>* BinTree<T>::findMaxNode(TreeNode<T>* pRoot)
{
	if (pRoot->_rightChild == nullptr)
	{
		return pRoot;
	}

	return findMaxNode(pRoot->_rightChild);
}

template<class T>
inline TreeNode<T>* BinTree<T>::removeMinNode(TreeNode<T>* pRoot)
{
	if (pRoot->_leftChild == nullptr)
	{
		TreeNode<T>* pNode = pRoot->_rightChild;
		delete pRoot;
		pRoot = nullptr;

		return pNode;
	}

	pRoot->_leftChild = removeMinNode(pRoot->_leftChild);
	return pRoot;
}

template<class T>
inline TreeNode<T>* BinTree<T>::removeMaxNode(TreeNode<T>* pRoot)
{
	if (pRoot->_rightChild == nullptr)
	{
		TreeNode<T>* pNode = pRoot->_leftChild;
		delete pRoot;
		pRoot = nullptr;

		return pNode;
	}
	pRoot->_rightChild = removeMaxNode(pRoot->_rightChild);
	return pRoot;
}

template<class T>
inline int BinTree<T>::getHeight(TreeNode<T>* pRoot)
{
	if (pRoot == nullptr)
	{
		return 0;
	}

	int leftH = getHeight(pRoot->_leftChild);
	int rightH = getHeight(pRoot->_rightChild);
	return leftH > rightH ? (leftH + 1) : (rightH + 1);
}

template<class T>
inline TreeNode<T>* BinTree<T>::removeElement(TreeNode<T>* pRoot, T elem)
{
	if (elem < pRoot->_data)
	{
		pRoot->_leftChild = removeElement(pRoot->_leftChild, elem);
		return pRoot;
	}

	if (elem > pRoot->_data)
	{
		pRoot->_rightChild = removeElement(pRoot->_rightChild, elem);
		return pRoot;
	}

	//elem == pRoot->_data
	if (pRoot->_leftChild == nullptr)
	{
		TreeNode<T>* pNode = pRoot->_rightChild;
		delete pRoot;
		pRoot = nullptr;
		return pNode;
	}

	if (pRoot->_rightChild == nullptr)
	{
		TreeNode<T>* pNode = pRoot->_leftChild;
		delete pRoot;
		pRoot = nullptr;
		return pNode;
	}

	TreeNode<T>* pSuccessor = findMinNode(pRoot);
	pRoot->_data = pSuccessor->_data;
	pRoot->_leftChild = pSuccessor->_leftChild;
	
	delete pSuccessor;
	pSuccessor = nullptr;

	return pRoot;
}
