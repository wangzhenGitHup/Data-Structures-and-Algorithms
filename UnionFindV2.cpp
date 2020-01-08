#include "pch.h"
#include "UnionFindV2.h"

UnionFindV2::UnionFindV2(int size)
{
	m_parent.resize(size);
	m_childCntVec.resize(size);

	for (int i = 0; i < size; i++)
	{
		m_parent[i] = i;
		m_childCntVec[i] = 1;
	}
}

int UnionFindV2::GetSize()
{
	return m_parent.size();
}

bool UnionFindV2::IsConnected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFindV2::UnionElements(int p, int q)
{
	int pRoot = find(p);
	int qRoot = find(q);

	if (pRoot == qRoot)
	{
		return;
	}

	if (m_childCntVec[pRoot] < m_childCntVec[qRoot])
	{
		m_parent[pRoot] = qRoot;
		m_childCntVec[qRoot] += m_childCntVec[pRoot];
	}
	else
	{
		m_parent[qRoot] = pRoot;
		m_childCntVec[pRoot] += m_childCntVec[qRoot];
	}
}

int UnionFindV2::find(int p)
{
	if (p < 0 && p >= m_parent.size())
	{
		throw "IllegalArgumnetException";
	}

	while (p != m_parent[p])
	{
		p = m_parent[p];
	}

	return p;
}
