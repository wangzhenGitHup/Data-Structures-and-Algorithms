#pragma once

#include "UnionFindInterface.h"
#include<vector>

class UnionFindV1 : public UnionFindInterface
{
public:
	UnionFindV1(int size);
	virtual int GetSize();
	virtual bool IsConnected(int p, int q);
	virtual void UnionElements(int p, int q);

private:
	int find(int p);

private:
	std::vector<int> m_DataVec;
};
