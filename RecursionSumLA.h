#pragma once

#include<iostream>
#include<vector>

int RecursionSum(std::vector<int>& data, int len)
{
	if (len == data.size())
	{
		return 0;
	}

	return data[len] + RecursionSum(data, len + 1);
}

void ArraySum()
{
	std::vector<int> tmpVec;
	tmpVec.push_back(1);
	tmpVec.push_back(11);
	tmpVec.push_back(10);
	tmpVec.push_back(5);
	tmpVec.push_back(2);
	tmpVec.push_back(3);
	tmpVec.push_back(4);
	tmpVec.push_back(6);

	std::cout << "Sum = " << RecursionSum(tmpVec, 0) << std::endl;
}

