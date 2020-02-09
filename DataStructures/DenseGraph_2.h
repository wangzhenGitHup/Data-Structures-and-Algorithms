#pragma once

#include<vector>
#include<cassert>
#include<iostream>
#include "Edge.h"
/*
	稠密图-----邻接矩阵
*/
template<class Weight>
class DenseGraph2
{
public:
	DenseGraph2(int v, bool isDirected)
	{
		m_vertex = v;
		m_edge = 0;
		m_bDirected = isDirected;

		for (int i = 0; i < v; i++)
		{
			m_graph.push_back(std::vector<Edge<Weight>* >(v, nullptr));
		}
	}

	~DenseGraph2()
	{
		for (int i = 0; i < m_vertex; i++)
		{
			for (int j = 0; j < m_vertex; j++)
			{
				if (m_graph[i][j])
				{
					delete m_graph[i][j];
				}
			}
		}
	}

	int GetVertex() { return m_vertex; }
	int GetEdge() { return m_edge; }
	void CreateEdge(int v1, int v2, Weight w)
	{
		assert(v1 >= 0 && v1 < m_vertex);
		assert(v2 >= 0 && v2 < m_vertex);

		if (HasEdge(v1, v2))
		{
			delete m_graph[v1][v2];
			if (!m_bDirected)
			{
				delete m_graph[v2][v1];
			}
			m_edge--;
		}

		m_graph[v1][v2] = new Edge<Weight>(v1, v2, w);
		if (!m_bDirected) m_graph[v2][v1] = new Edge<Weight>(v2, v1, w);
		m_edge++;
	}

	bool HasEdge(int v1, int v2)
	{
		assert(v1 >= 0 && v1 < m_vertex);
		assert(v2 >= 0 && v2 < m_vertex);
		return m_graph[v1][v2] != nullptr;
	}

	void Show()
	{
		for (int i = 0; i < m_vertex; i++)
		{
			for (int j = 0; j < m_vertex; j++)
			{
				if (m_graph[i][j])
				{
					std::cout << m_graph[i][j]->GetWeight() << "\t";
				}
				else
				{
					std::cout << "null\t";
				}
			}
			std::cout << std::endl;
		}
	}

	class AdjIterator
	{
	public:
		AdjIterator(DenseGraph& g, int v) : m_graph(g), m_vertex(v)
		{
			m_index = -1;
		}

		Edge<Weight>* Begin()
		{
			m_index = -1;
			return Next();
		}

		Edge<Weight>* Next()
		{
			for (m_index += 1; m_index < m_graph.GetVertex(); m_index++)
			{
				if (m_graph.m_graph[m_vertex][m_index])
				{
					return m_graph.m_graph[m_vertex][m_index];
				}
			}

			return nullptr;
		}

		bool End()
		{
			return m_index >= m_graph.GetVertex();
		}

	private:
		DenseGraph2 & m_graph;
		int m_vertex;
		int m_index;
	};

private:
	int m_vertex; //节点
	int m_edge; //边
	bool m_bDirected; //是否是有向图
	std::vector<std::vector<Edge<Weight>* >> m_graph;
};