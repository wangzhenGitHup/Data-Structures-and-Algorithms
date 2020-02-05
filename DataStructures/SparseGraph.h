#pragma once

#include<vector>

/*
	ϡ��ͼ----�ڽӱ�
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
	int m_vertex; //�ڵ�
	int m_edge; //��
	bool m_bDirected; //�Ƿ�������ͼ
	std::vector<std::vector<int>> m_graph;
};
