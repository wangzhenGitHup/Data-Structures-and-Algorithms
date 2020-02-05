#pragma once

#include<vector>

/*
	稀疏图----邻接表
*/
class SparseGraph
{
public:
	SparseGraph(int v, bool isDirected);
	~SparseGraph()
	{

	}

	void CreateEdge(int v1, int v2);
	bool HasEdge(int v1, int v2);

	class AdjIterator
	{
	public:
		AdjIterator(SparseGraph& g, int v): m_graph(g), m_vertex(v)
		{
			m_index = 0;
		}

		int Begin()
		{
			m_index = 0;
			if (m_graph.m_graph[m_vertex].size() > 0)
			{
				return m_graph.m_graph[m_vertex][m_index];
			}

			return -1;
		}

		int Next()
		{
			m_index++;
			if (m_index < m_graph.m_graph[m_vertex].size())
			{
				return m_graph.m_graph[m_vertex][m_index];
			}

			return -1;
		}

		bool End()
		{
			return m_index >= m_graph.m_graph[m_vertex].size();
		}

	private:
		SparseGraph & m_graph;
		int m_vertex;
		int m_index;
	};

private:
	int m_vertex; //节点
	int m_edge; //边
	bool m_bDirected; //是否是有向图
	std::vector<std::vector<int>> m_graph;
};
