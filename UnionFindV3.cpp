#include "pch.h"
#include "UnionFindV3.h"

UnionFindV3::UnionFindV3(int size)
{
	m_parent.resize(size);
	for (int i = 0; i < size; i++)
	{
		m_parent[i] = i;
		m_rank[i] = 1;
	}
}

int UnionFindV3::GetSize()
{
	return m_parent.size();
}

bool UnionFindV3::IsConnected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFindV3::UnionElements(int p, int q)
{
	int pRoot = find(p);
	int qRoot = find(q);

	if (pRoot == qRoot)
	{
		return;
	}

	if (m_rank[pRoot] < m_rank[qRoot])
	{
		m_parent[pRoot] = qRoot;
	}
	else if (m_rank[qRoot] < m_rank[pRoot])
	{
		m_parent[qRoot] = pRoot;
	}
	else
	{
		m_parent[pRoot] = qRoot;
		m_rank[pRoot] += 1;
	}
}

int UnionFindV3::find(int p)
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
