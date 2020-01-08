#include "pch.h"
#include "UnionFindV1.h"

UnionFindV1::UnionFindV1(int size)
{
	m_DataVec.resize(size);
	for (int i = 0; i < size; i++)
	{
		m_DataVec[i] = i;
	}
}

int UnionFindV1::GetSize()
{
	return m_DataVec.size();
}

bool UnionFindV1::IsConnected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFindV1::UnionElements(int p, int q)
{
	int pID = find(p);
	int qID = find(q);

	if (pID == qID)
	{
		return;
	}

	for (int i = 0; i < m_DataVec.size(); i++)
	{
		if (m_DataVec[i] == pID)
		{
			m_DataVec[i] = qID;
		}
	}
}

int UnionFindV1::find(int p)
{
	if (p < 0 && p >= m_DataVec.size())
	{
		throw "IllegalArgumnetException";
	}

	return m_DataVec[p];
	return 0;
}
