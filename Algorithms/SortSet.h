#pragma once
#include <iostream>
#include <ctime>

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
	static void __sort(T arr[], int left, int right)
	{
		if (left >= right)
		{
			return;
		}

		int pos = __partition(arr, left, right);
		__sort(arr, left, pos - 1);
		__sort(arr, pos + 1, right);
	}

	static int __partition(T arr[], int left, int right)
	{
		std::swap(arr[left], arr[rand() % (right - left + 1) + left]);
		T tmpElem = arr[left];
		int j = left;
		for (int i = left + 1; i <= right; i++)
		{
			if (arr[i] < tmpElem)
			{
				std::swap(arr[++j], arr[i]);
			}
		}

		std::swap(arr[left], arr[j]);
		return j;
	}
};