#include "DenseGraph.h"
#include<cassert>
#include<iostream>

DenseGraph::DenseGraph(int v, bool isDirected)
{
	m_vertex = v;
	m_edge = 0;
	m_bDirected = isDirected;

	for (int i = 0; i < v; i++)
	{
		m_graph.push_back(std::vector<bool>(v, false));
	}
}

void DenseGraph::CreateEdge(int v1, int v2)
{
	assert(v1 >= 0 && v1 < m_vertex);
	assert(v2 >= 0 && v2 < m_vertex);

	if (HasEdge(v1, v2))return;
	m_graph[v1][v2] = true;
	if (!m_bDirected) m_graph[v2][v1] = true;
	m_edge++;
}

bool DenseGraph::HasEdge(int v1, int v2)
{
	assert(v1 >= 0 && v1 < m_vertex);
	assert(v2 >= 0 && v2 < m_vertex);
	return m_graph[v1][v2];
}

void DenseGraph::Show()
{
	for (int i = 0; i < m_vertex; i++)
	{
		for (int j = 0; j < m_vertex; j++)
		{
			std::cout << m_graph[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
