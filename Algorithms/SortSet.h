#pragma once
#include <iostream>

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
		__mergeSort(arr, 0, len - 1);
	}

private:
	static void __mergeSort(T arr[], int left, int right)
	{
		if (right - left <= 100)
		{
			insertSort(arr, left, right);
			return;
		}

		int mid = (left + right) >> 1;
		__mergeSort(arr, left, mid);
		__mergeSort(arr, mid + 1, right);
		if (arr[mid] > arr[mid + 1])
		{
			__merge(arr, left, mid, right);
		}
	}

	static void __merge(T arr[], int left, int mid, int right)
	{
		T *tmpSpace = new T[right - left + 1];
		int i = left;

		for (; i <= right; i++)
		{
			tmpSpace[i - left] = arr[i];
		}

		i = left;
		int j = mid + 1;
		for (int k = left; k <= right; k++)
		{
			if (i > mid)
			{
				arr[k] = tmpSpace[j - left];
				j++;
			}
			else if (j > right)
			{
				arr[k] = tmpSpace[i - left];
				i++;
			}
			else if(tmpSpace[i - left] < tmpSpace[j - left])
			{ 
				arr[k] = tmpSpace[i - left];
				i++;
			}
			else
			{
				arr[k] = tmpSpace[j - left];
				j++;
			}
		}

		delete[] tmpSpace;
	}
};