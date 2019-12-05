#pragma once

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
	void InOrder();

private:
	TreeNode<T>* addChild(TreeNode<T>* pRoot, T elem);
	void copy(const TreeNode<T>* pRoot);
	bool contains(const TreeNode<T>* pRoot, T elem);
	void preOrder(TreeNode<T>* pRoot);
	void inOrder(TreeNode<T>* pRoot);

private:
	TreeNode<T>* _root;
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
inline void BinTree<T>::InOrder()
{
	inOrder(_root);
	std::cout << std::endl;
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
