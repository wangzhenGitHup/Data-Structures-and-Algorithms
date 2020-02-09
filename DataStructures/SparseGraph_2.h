#pragma once

#include<vector>
#include<cassert>
#include<iostream>
#include "Edge.h"

/*
	稀疏图----邻接表
*/
template<class Weight>
class SparseGraph
{
public:
	SparseGraph(int v, bool isDirected)
	{
		m_vertex = v;
		m_bDirected = isDirected;
		m_edge = 0;

		for (int i = 0; i < v; i++)
		{
			m_graph.push_back(std::vector<Edge<Weight>*>());
		}
	}

	~SparseGraph()
	{
		for (int i = 0; i < m_vertex; i++)
		{
			for (int j = 0; j < m_graph[i].size(); j++)
			{
				delete m_graph[i][j];
			}
		}
	}

	void CreateEdge(int v1, int v2, Weight w)
	{
		assert(v1 >= 0 && v1 < m_vertex);
		assert(v2 >= 0 && v2 < m_vertex);

		m_graph[v1].push_back(new Edge(v1, v2, w));
		if (v1 != v2 && !m_bDirected)m_graph[v2].push_back(new Edge(v2, v1, w));
		m_edge++;
	}

	bool HasEdge(int v1, int v2)
	{
		assert(v1 >= 0 && v1 < m_vertex);
		assert(v2 >= 0 && v2 < m_vertex);
		for (int i = 0; i < m_graph[v1].size(); i++)
		{
			if (m_graph[v1][i]->GetOtherVertex(v) == v2)
			{
				return true;
			}
		}
		return false;
	}
	int GetVertex() { return m_vertex; }
	int GetEdge() { return m_edge; }
	void Show()
	{
		for (int i = 0; i < m_vertex; i++)
		{
			std::cout << "vertex " << i << ":\t";
			for (int j = 0; j < m_graph[i].size(); j++)
			{
				std::cout << "( to: " <<m_graph[i][j]->GetEdge() << ", weight: " << m_graph[i][j]->GetWeight() << "\t";
			}
			std::cout << std::endl;
		}
	}

	class AdjIterator
	{
	public:
		AdjIterator(SparseGraph& g, int v): m_graph(g), m_vertex(v)
		{
			m_index = 0;
		}

		Edge<Weight>* Begin()
		{
			m_index = 0;
			if (m_graph.m_graph[m_vertex].size() > 0)
			{
				return m_graph.m_graph[m_vertex][m_index];
			}

			return nullptr;
		}

		Edge<Weight>* Next()
		{
			m_index++;
			if (m_index < m_graph.m_graph[m_vertex].size())
			{
				return m_graph.m_graph[m_vertex][m_index];
			}

			return nullptr;
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
	std::vector<std::vector<Edge<Weight>* >> m_graph;
};
