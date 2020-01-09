#pragma once

template<class T>
class SegmentTree
{
public:
	SegmentTree(const T* data, int len);
	~SegmentTree();
	int GetSize();
	T GetData(int idx);
	T Query(int queryLeft, int queryRight);
	void Update(int idx, T elem);

private:
	int leftChild(int idx);
	int rightChild(int idx);
	void buildSegmentTree(int treeIdx, int leftIdx, int rightIdx);
	T query(int treeIdx, int rangeLeft, int rangeRight, int queryLeft, int queryRight);
	void set(int treeIdx, int rangeLeft, int rangeRight, int idx, T elem);

private:
	const int _MulitiNum = 4;
	T* _array = nullptr;
	T* _tree = nullptr;
	int _size;
};

template<class T>
SegmentTree<T>::SegmentTree(const T* data, int len)
{
	_array = new T[len];
	for (int i = 0; i < len; i++)
	{
		_array[i] = data[i];
	}
	_size = len;

	_tree = new T[_MulitiNum * len];

	buildSegmentTree(0, 0, _size - 1);
}

template<class T>
SegmentTree<T>::~SegmentTree()
{
	delete[]_array;
	_array = nullptr;

	delete[] _tree;
	_tree = nullptr;
}

template<class T>
int SegmentTree<T>::GetSize()
{
	return _size;
}

template<class T>
T SegmentTree<T>::GetData(int idx)
{
	if (idx < 0 || idx >= _size)
	{
		throw "Index Error";
	}

	return _array[idx];
}

template<class T>
T SegmentTree<T>::Query(int queryLeft, int queryRight)
{
	if (queryLeft < 0 || queryLeft >= _size ||
		queryRight < 0 || queryRight >= _size ||
		queryLeft > queryRight)
	{
		throw "query idx error!";
	}

	return query(0, 0, _size - 1, queryLeft, queryRight);
}

template<class T>
void SegmentTree<T>::Update(int idx, T elem)
{
	if (idx < 0 || idx >= _size - 1)
	{
		return;
	}

	_array[idx] = elem;
	set(0, 0, _size - 1, idx, elem);
}

template<class T>
int SegmentTree<T>::leftChild(int idx)
{
	return (idx << 1) + 1;
}

template<class T>
int SegmentTree<T>::rightChild(int idx)
{
	return (idx << 1) + 2;
}

template<class T>
void SegmentTree<T>::buildSegmentTree(int treeIdx, int leftIdx, int rightIdx)
{
	if (leftIdx == rightIdx)
	{
		_tree[treeIdx] = _array[leftIdx];
		return;
	}

	int leftTreeIdx = leftChild(treeIdx);
	int rightTreeIdx = leftChild(treeIdx);
	int mid = leftIdx + (rightIdx - 1) / 2;

	buildSegmentTree(leftTreeIdx, leftIdx, mid);
	buildSegmentTree(rightTreeIdx, mid + 1, rightIdx);

	_tree[treeIdx] = _tree[leftTreeIdx] + _tree[rightTreeIdx];
}

template<class T>
T SegmentTree<T>::query(int treeIdx, 
	int rangeLeft, int rangeRight, 
	int queryLeft, int queryRight)
{
	if (rangeLeft == queryLeft && rangeRight == queryRight)
	{
		return _tree[treeIdx];
	}

	int mid = rangeLeft + (rangeRight - 1) / 2;
	int treeLeftIdx = leftChild(treeIdx);
	int treeRightIdx = rightChild(treeIdx);

	if (queryLeft >= mid +1)
	{
		return query(treeRightIdx, mid + 1, rangeRight, queryLeft, queryRight);
	}

	if (queryRight <= mid)
	{
		return query(treeLeftIdx, rangeLeft, mid, queryLeft, queryRight);
	}

	T leftRet = query(treeLeftIdx, rangeLeft, mid, queryLeft, mid);
	T rightRet = query(treeRightIdx, mid + 1, rangeRight, mid + 1, queryRight);

	return leftRet + rightRet;
}

template<class T>
void SegmentTree<T>::set(int treeIdx, int rangeLeft, int rangeRight, int idx, T elem)
{
	if (rangeLeft == rangeRight)
	{
		_tree[treeIdx] = elem;
		return;
	}

	int mid = rangeLeft + (rangeRight - 1) / 2;
	int treeLeftChild = leftChild(treeIdx);
	int treeRightChild = rightChild(treeIdx);

	if (idx >= mid + 1)
	{
		set(treeRightChild, mid + 1, rangeRight, idx, elem);
	}
	else
	{
		set(treeLeftChild, rangeLeft, mid, idx, elem);
	}

	_tree[treeIdx] = _tree[treeLeftChild] + _tree[treeRightChild];
}
