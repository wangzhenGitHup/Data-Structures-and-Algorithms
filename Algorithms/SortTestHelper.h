#pragma once

#include<iostream>
#include<ctime>
#include<cassert>

namespace SortTestHelper
{
	template<typename T>
	std::shared_ptr<T[]> GeneratorRandomArray(int count, int rangeLeft, int rangeRight)
	{
		//int* pArray = new int[count];
		std::shared_ptr<T[]> pArray(new int[count]);

		srand(time(NULL));
		for (int i = 0; i < count; i++)
		{
			assert(rangeLeft <= rangeRight);
			int value = rand() % (rangeRight - rangeLeft + 1) + rangeLeft;
			pArray[i] = value;
		}

		return pArray;
	}

	template<typename T>
	bool isSorted(T arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	void TestSort(std::string sortName, void(*sort)(T[], int), T arr[], int n)
	{
		clock_t startTime = clock();

		sort(arr, n);

		clock_t endTime = clock();

		assert(isSorted(arr, n));
		std::cout << sortName << ": " << double(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
	}

	template<typename T>
	void TestSort(std::string sortName, void(*sort)(T[], int, int), T arr[], int n)
	{
		clock_t startTime = clock();

		sort(arr, 0, n - 1);

		clock_t endTime = clock();

		assert(isSorted(arr, n));
		std::cout << sortName << ": " << double(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
	}

	template<typename T>
	std::shared_ptr<T[]> CopyArrayElement(std::shared_ptr<T[]>& pArray, int len)
	{
		std::shared_ptr<T[]> arrayData(new T[len]);
		for (int i = 0; i < len; i++)
		{
			arrayData[i] = pArray[i];
		}
		return arrayData;
	}

}
