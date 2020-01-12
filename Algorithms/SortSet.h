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
		for (j = i; j > 0 && arr[j - 1] > tmpElem; j--)
		{
			arr[j] = arr[j - 1];
		}

		arr[j] = tmpElem;
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