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