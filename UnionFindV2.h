#pragma once

#include "UnionFindInterface.h"
#include<vector>

class UnionFindV2 : public UnionFindInterface
{
public:
	UnionFindV2(int size);
	virtual int GetSize();
	virtual bool IsConnected(int p, int q);
	virtual void UnionElements(int p, int q);

private:
	int find(int p);

private:
	std::vector<int> m_parent;
	std::vector<int> m_childCntVec; //表示某序号为根的集合中元素的个数
};
