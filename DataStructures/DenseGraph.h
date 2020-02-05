#pragma once

#include<vector>

/*
	稠密图-----邻接矩阵
*/
class DenseGraph
{
public:
	DenseGraph(int v, bool isDirected);
	~DenseGraph()
	{

	}

	int GetVertex() { return m_vertex; }
	int GetEdge() { return m_edge; }
	void CreateEdge(int v1, int v2);
	bool HasEdge(int v1, int v2);
	void Show();

	class AdjIterator
	{
	public:
		AdjIterator(DenseGraph& g, int v) : m_graph(g), m_vertex(v)
		{
			m_index = -1;
		}

		int Begin()
		{
			m_index = -1;
			return Next();
		}

		int Next()
		{
			for (m_index += 1; m_index < m_graph.GetVertex(); m_index++)
			{
				if (m_graph.m_graph[m_vertex][m_index])
				{
					return m_index;
				}
			}

			return -1;
		}

		bool End()
		{
			return m_index >= m_graph.GetVertex();
		}

	private:
		DenseGraph & m_graph;
		int m_vertex;
		int m_index;
	};

private:
	int m_vertex; //节点
	int m_edge; //边
	bool m_bDirected; //是否是有向图
	std::vector<std::vector<bool>> m_graph;
};