#pragma once

#include "UnionFindInterface.h"
#include<vector>

class UnionFindV3 : public UnionFindInterface
{
public:
	UnionFindV3(int size);
	virtual int GetSize();
	virtual bool IsConnected(int p, int q);
	virtual void UnionElements(int p, int q);

private:
	int find(int p);

private:
	std::vector<int> m_parent;
	std::vector<int> m_rank; //表示某序号为根的集合所表示的树的层数

};