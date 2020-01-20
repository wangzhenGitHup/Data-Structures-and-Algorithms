#pragma once
#include <iostream>
#include <ctime>
#include<cassert>

template<typename T>
void show(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}

template<typename T>
void selectSort(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int minIdx = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[minIdx] > arr[j])
			{
				minIdx = j;
			}
		}

		std::swap(arr[i], arr[minIdx]);
	}
}

template<typename T>
void insertSort(T arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		T tmpElem = arr[i];
		int j = i;
		for (; j > 0 && arr[j - 1] > tmpElem; j--)
		{
			arr[j] = arr[j - 1];
		}

		arr[j] = tmpElem;
	}
}

template<typename T>
void insertSort(T arr[], int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		T elem = arr[i];
		int j = i;
		for (; j > left && arr[j - 1] > elem; j--)
		{
			arr[j] = arr[j - 1];
		}

		arr[j] = elem;
	}
}

template<typename T>
void bubbleSort(T arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		bool isSort = true;
		for (int j = len - 1; j > i; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				std::swap(arr[j - 1], arr[j]);
				isSort = false;
			}
		}

		if (isSort)
		{
			break;
		}
	}
}

template<typename T>
void shellSort(T arr[], int len)
{
	int n = len >> 1;
	while (n > 0)
	{
		for (int i = n; i < len; i++)
		{
			T tmpElem = arr[i];
			int j = i;
			for (j = i; j > 0 && arr[j - 1] > tmpElem; j--)
			{
				arr[j] = arr[j - 1];
			}

			arr[j] = tmpElem;
		}
		n = n >> 1;
	}
}

template<class T>
class MergeSort
{
public:
	static void mergeSort(T arr[], int len)
	{
		T *tempArr = new T[len];
		__mergeSort(arr, tempArr, 0, len - 1);
		delete tempArr;
	}

private:
	static void __mergeSort(T arr[], T tempArr[], int startIdx, int endIdx)
	{
		if (endIdx - startIdx <= 100)
		{
			insertSort(arr, startIdx, endIdx);
			return;
		}

		//中部下标
		int midIdx = startIdx + ((endIdx - startIdx) >> 1);

		__mergeSort(arr, tempArr, startIdx, midIdx);
		__mergeSort(arr, tempArr, midIdx + 1, endIdx);
		if (arr[midIdx] > arr[midIdx + 1])
		{
			__merge(arr, tempArr, startIdx, midIdx, endIdx);
		}
	}

	static void __merge(T arr[], T tempArr[], int startIdx, int midIdx, int endIdx)
	{
		//复制要合并的数据
		for (int i = startIdx; i <= endIdx; i++)
		{
			tempArr[i] = arr[i];
		}

		int left = startIdx; //左边首位下标
		int right = midIdx + 1; //右边首位下标

		for (int k = startIdx; k <= endIdx; k++)
		{
			if (left > midIdx) //如果左边的首位下标大于中部下标，证明左边的数据已经排序完了
			{
				arr[k] = tempArr[right++];
			}
			else if (right > endIdx)
			{
				arr[k] = tempArr[left++]; //如果右边的首位下标大于数组长度，证明右边的数据已经排序完了
			}
			else if (tempArr[right] < tempArr[left])
			{
				arr[k] = tempArr[right++]; //将右边的首位排入，然后右边的下标指针自增
			}
			else
			{
				arr[k] = tempArr[left++]; //将左边的首位排入，然后左边的下标指针自增
			}
		}
	}
};

template<class T>
class QuickSort
{
public:
	static void Sort(T arr[], int len)
	{
		srand(time(NULL));
		__sort(arr, 0, len - 1);
	}

private:
	static void __sort(T arr[], int startIdx, int endIdx)
	{
		if (startIdx >= endIdx)
		{
			return;
		}

		int pivotIdx = __partition2(arr, startIdx, endIdx);
		__sort(arr, startIdx, pivotIdx - 1);
		__sort(arr, pivotIdx + 1, endIdx);
	}

	static int __partition2(T arr[], int startIdx, int endIdx)
	{
		std::swap(arr[startIdx], arr[rand() % (endIdx - startIdx + 1) + startIdx]);
		T pivotElem = arr[startIdx];
		int leftIdx = startIdx;
		int rightIdx = endIdx;

		while (true)
		{
			//从左往右扫描
			while (arr[leftIdx] <= pivotElem)
			{
				leftIdx++;
				if (leftIdx == rightIdx)
				{
					break;
				}
			}

			//从右往左扫描
			while (pivotElem < arr[rightIdx])
			{
				rightIdx--;
				if (leftIdx == rightIdx)
				{
					break;
				}
			}

			//左右下标相遇
			if (leftIdx >= rightIdx)
			{
				break;
			}

			std::swap(arr[leftIdx], arr[rightIdx]);
		}

		//将基准值插入序列
		std::swap(arr[startIdx], arr[rightIdx]);
		return rightIdx;
	}
};

template<class Item>
class MaxHeap
{
public:
	explicit MaxHeap(unsigned int capacity)
	{
		m_capacity = capacity;
		m_data = new Item[capacity + 1];
		m_size = 0;
	}

	MaxHeap(Item arr[], unsigned int n)
	{
		

		m_capacity = n;
		m_size = n;
		for (unsigned int i = 0; i < n; i++)
		{
			m_data[i + 1] = arr[i];
		}

		for (unsigned int idx = m_size / 2; idx >= 1; idx--)
		{
			shiftDown(idx);
		}
		
	}

	~MaxHeap()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	unsigned int GetSize() { return m_size; }
	bool IsEmpty() { return m_size == 0; }
	void Insert(Item item)
	{
		assert(m_capacity > m_size + 1);
		m_data[++m_size] = item;
		shiftUp(m_size);
	}

	Item ExtractMax()
	{
		assert(m_size > 0);
		Item ret = m_data[1];
		std::swap(m_data[1], m_data[m_size]);
		m_size--;
		shiftDown(1);
		return ret;
	}

private:
	void shiftUp(unsigned int idx)
	{
		while (idx > 1 && m_data[idx / 2] < m_data[idx])
		{
			std::swap(m_data[idx / 2], m_data[idx]);
			idx /= 2;
		}
	}

	void shiftDown(unsigned int idx)
	{
		while ((idx << 1) <= m_size)
		{
			unsigned int childIdx = idx << 1;
			if (childIdx + 1 <= m_size &&
				m_data[childIdx + 1] > m_data[childIdx])
			{
				childIdx += 1;
			}

			if (m_data[idx] >= m_data[childIdx])
			{
				break;
			}

			std::swap(m_data[idx], m_data[childIdx]);
			idx = childIdx;
		}
	}

private:
	Item* m_data;
	unsigned int m_size;
	unsigned int m_capacity;
};

template<typename T>
void heapSort(T arr[], unsigned int n)
{
	MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);
	for (unsigned int i = n - 1; i >= 0; i--)
	{
		arr[i] = maxHeap.ExtractMax();
	}
}

template<class T>
class HeapSort
{
public:
	static void sort(T arr[], unsigned int n)
	{
		for (unsigned int i = (n - 1) / 2; i >= 0; i--)
		{
			__shiftDown(arr, n, i);
		}

		for (unsigned int i = n - 1; i > 0; i--)
		{
			std::swap(arr[0], arr[i]);
			__shiftDown(arr, i, 0);
		}
	}


private:
	static void __shiftDown(T arr[], unsigned int n, unsigned int idx)
	{
		while ((idx << 1) + 1 < n)
		{
			unsigned int childIdx = (idx << 1) + 1;
			if (childIdx + 1 < n &&
				arr[childIdx + 1] > arr[childIdx])
			{
				childIdx += 1;
			}

			if (arr[idx] >= arr[childIdx])
			{
				break;
			}

			std::swap(arr[idx], arr[childIdx]);
			idx = childIdx;
		}
	}
};

