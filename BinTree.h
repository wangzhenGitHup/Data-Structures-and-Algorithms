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
	
private:
	void _addChild(TreeNode<T>* pRoot, T elem);
	void copy(const TreeNode<T>* pRoot);

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
	if (_root == nullptr)
	{
		_root = new TreeNode<T>(elem);
	}
	else
	{
		_addChild(_root, elem);
	}
}

template<class T>
inline void BinTree<T>::_addChild(TreeNode<T>* pRoot, T elem)
{
	if (elem == pRoot->_data)
	{
		return;
	}
	
	if (elem < pRoot->_data)
	{
		if (pRoot->_leftChild == nullptr)
		{
			pRoot->_leftChild = new TreeNode<T>(elem);
		}
		else
		{
			_addChild(pRoot->_leftChild, elem);
		}
	}
	else if (elem > pRoot->_data)
	{
		if (pRoot->_rightChild == nullptr)
		{
			pRoot->_rightChild = new TreeNode<T>(elem);
		}
		else
		{
			_addChild(pRoot->_rightChild, elem);
		}
	}
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
