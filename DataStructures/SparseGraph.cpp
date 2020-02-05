#include "SparseGraph.h"
#include<cassert>
#include<iostream>

SparseGraph::SparseGraph(int v, bool isDirected)
{
	m_vertex = v;
	m_bDirected = isDirected;
	m_edge = 0;

	for (int i = 0; i < v; i++)
	{
		m_graph.push_back(std::vector<int>());
	}
}

void SparseGraph::CreateEdge(int v1, int v2)
{
	assert(v1 >= 0 && v1 < m_vertex);
	assert(v2 >= 0 && v2 < m_vertex);

	m_graph[v1].push_back(v2);
	if (v1 != v2 && !m_bDirected)m_graph[v2].push_back(v1);
	m_edge++;
}

bool SparseGraph::HasEdge(int v1, int v2)
{
	assert(v1 >= 0 && v1 < m_vertex);
	assert(v2 >= 0 && v2 < m_vertex);
	for (int i = 0; i < m_graph[v1].size(); i++)
	{
		if (m_graph[v1][i] == v2)
		{
			return true;
		}
	}
	return false;
}

void SparseGraph::Show()
{
	for (int i = 0; i < m_vertex; i++)
	{
		std::cout << "vertex " << i << ":\t";
		for (int j = 0; j < m_graph[i].size(); j++)
		{
			std::cout << m_graph[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
