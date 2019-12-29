#pragma once

template<class T>
class SegmentTree
{
public:
	SegmentTree(const T* data, int len);
	~SegmentTree();
	int GetSize();
	T GetData(int idx);

private:
	int leftChild(int idx);
	int rightChild(int idx);
	void buildSegmentTree(int treeIdx, int leftIdx, int rightIdx);

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

	buildSegmentTree(leftTreeIdx, leftIdx, mide);
	buildSegmentTree(rightTreeIdx, mid + 1, rightIdx);

	_tree[treeIdx] = _tree[leftTreeIdx] + _tree[rightTreeIdx];
}
