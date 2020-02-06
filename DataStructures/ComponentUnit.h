#pragma once

#include <cassert>

template<class Graph>
class ComponentUnit
{
public:
	ComponentUnit(Graph& g) : m_graph(g)
	{
		m_bVisitedList = new bool[g.GetVertex()];
		m_connectVertexList = new int[g.GetVertex()];

		m_count = 0;
		for (int i = 0; i < g.GetVertex(); i++)
		{
			m_bVisitedList[i] = false;
			m_connectVertexList[i] = -1;
		}

		for (int i = 0; i < g.GetVertex(); i++)
		{
			if (!m_bVisitedList[i])
			{
				dfs(i);
				m_count++;
			}
		}
	}

	~ComponentUnit()
	{
		delete[] m_bVisitedList;
		delete[] m_connectVertexList;
	}

	int GetCount() { return m_count; }
	bool IsConnected(int v1, int v2)
	{
		assert(v1 >= 0 && v1 < m_graph.GetVertex());
		assert(v2 >= 0 && v2 < m_graph.GetVertex());
		return m_connectVertexList[v1] == m_connectVertexList[v2];
	}

private:
	void dfs(int v)
	{
		m_bVisitedList[v] = true;
		m_connectVertexList[v] = m_count;

		typename Graph::AdjIterator adj(m_graph, v);
		for (int i = adj.Begin(); !adj.End(); i = adj.Next())
		{
			if (!m_bVisitedList[i])
			{
				dfs(i);
			}
		}
	}

private:
	Graph &m_graph;
	bool *m_bVisitedList;
	int *m_connectVertexList;
	int m_count;
};