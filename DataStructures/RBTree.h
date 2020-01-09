#pragma once

template<class K, class V>
class RBTree
{
public:
	RBTree();
	~RBTree();
	int GetSize();
	bool IsEmpty();
	void Add(K key, V value);
	V GetValue(K key);
	void Set(K key, V value);

private:
	enum NodeColor
	{
		RED = 0,
		BLACK = 1,
	};

	struct TreeNode
	{
		TreeNode(K key, V value)
		{
			_key = key;
			_value = value;
			_leftChild = _rightChild = nullptr;
			_color = RED;
		}

		K _key;
		V _value;
		TreeNode* _leftChild;
		TreeNode* _rightChild;
		NodeColor _color;
	};

	TreeNode* addChild(TreeNode* pRoot, K key, V value)
	{
		if (pRoot == nullptr)
		{
			TreeNode* pNewNode = new TreeNode(key, value);
			_size++;
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
		else
		{
			pRoot->_value = value;
		}

		//红黑树性质维护
		
		//是否需要左旋转
		if (nodeColor(pRoot->_rightChild) == RED &&
			nodeColor(pRoot->_leftChild) == BLACK)
		{
			pRoot = leftRotate(pRoot);
		}

		//是否需要右旋转
		if (nodeColor(pRoot->_leftChild) == RED &&
			nodeColor(pRoot->_leftChild->_leftChild) == RED)
		{
			pRoot = rightRotate(pRoot);
		}

		//是否需要翻转颜色
		if (nodeColor(pRoot->_leftChild) == RED &&
			nodeColor(pRoot->_rightChild) == RED)
		{
			flipColor(pRoot);
		}
		return pRoot;
	}

	NodeColor nodeColor(TreeNode* pRoot)
	{
		if (pRoot == nullptr)
		{
			return BLACK;
		}

		return pRoot->_color;
	}
	/*
			pNode                          y
		   /     \                        / \
		  /       \        左旋转         /   \
	     x         y     --------->    pNode  b
		          / \                  / \
				 /   \                /   \
				a     b              x     a
	*/
	TreeNode* leftRotate(TreeNode* pNode)
	{
		TreeNode* pRNode = pNode->_rightChild;
		TreeNode* pRLNode = pRNode->_leftChild;

		pNode->_rightChild = pRLNode;
		pRNode->_leftChild = pNode;

		pRNode->_color = pNode->_color;
		pNode->_color = RED;

		return pRNode;
	}

	/*
			pNode                          x
		   /     \                        / \
		  /       \        右旋转         /   \
		 x         y     --------->     a     pNode
		/ \		                             /  \
	   /   \	                            /    \
	  a		b        				        b    y  

	*/
	TreeNode* rightRotate(TreeNode* pNode)
	{
		TreeNode* pLNode = pNode->_leftChild;
		TreeNode* pLRNode = pLNode->_rightChild;
		pNode->_leftChild = pLRNode;
		pLNode->_rightChild = pNode;

		pLNode->_color = pNode->_color;
		pNode->_color = RED;

		return pLNode;
	}

	void flipColor(TreeNode* pNode)
	{
		pNode->_color = RED;
		pNode->_leftChild->_color = BLACK;
		pNode->_rightChild->_color = BLACK;
	}

	TreeNode* getNode(TreeNode* pNode, K key)
	{
		if (pNode == nullptr)
		{
			return nullptr;
		}

		if (pNode->_key == key)
		{
			return pNode;
		}

		if (key < pNode->_key)
		{
			return getNode(pNode->_leftChild, key);
		}

		return getNode(pNode->_rightChild, key);
	}

	V getValue(TreeNode* pRoot, K key)
	{
		TreeNode* pNode = getNode(pRoot, key);
		if (pNode != nullptr)
		{
			return pNode->_value;
		}

		return V();
	}

	void setValue(TreeNode* pRoot, K key, V value)
	{
		TreeNode* pNode = getNode(pRoot, key);
		if (pNode != nullptr)
		{
			pNode->_value = value;
		}
	}

private:
	TreeNode* _root = nullptr;
	int _size;
};

template<class K, class V>
RBTree<K, V>::RBTree()
{
	_size = 0;
}

template<class K, class V>
RBTree<K, V>::~RBTree()
{
}

template<class K, class V>
inline int RBTree<K, V>::GetSize()
{
	return _size;
}

template<class K, class V>
inline bool RBTree<K, V>::IsEmpty()
{
	return _size == 0;
}

template<class K, class V>
void RBTree<K, V>::Add(K key, V value)
{
	_root = addChild(_root, key, value);
	_root->_color = BLACK;
}

template<class K, class V>
V RBTree<K, V>::GetValue(K key)
{
	return getValue(_root, key);
}

template<class K, class V>
void RBTree<K, V>::Set(K key, V value)
{
	setValue(_root, key, value);
}
