#pragma once

#include <cassert>
#include <vector>
#include <stack>
#include <iostream>

template<class Graph>
class DFS_Path
{
public:
	DFS_Path(Graph& g, int start) : m_graph(g)
	{
		assert(start >= 0 && start < g.GetVertex());

		m_startVertex = start;
		m_bVisitedList = new bool[g.GetVertex()];
		m_fromVertexList = new int[g.GetVertex()];

		for (int i = 0; i < g.GetVertex(); i++)
		{
			m_bVisitedList[i] = false;
			m_fromVertexList[i] = -1;
		}

		dfs(start);
	}

	~DFS_Path()
	{
		delete[] m_bVisitedList;
		delete[] m_fromVertexList;
	}

	bool HasPath(int v)
	{
		assert(v >= 0 && v < m_graph.GetVertex());
		return m_bVisitedList[v];
	}

	void Path(int v, std::vector<int>& pathVec)
	{
		int tmpV = v;
		std::stack<int> pathStack;
		while (tmpV != -1)
		{
			pathStack.push(tmpV);
			tmpV = m_fromVertexList[tmpV];
		}

		pathVec.clear();
		while (!pathStack.empty())
		{
			pathVec.push_back(pathStack.top());
			pathStack.pop();
		}
	}

	void ShowPath(int v)
	{
		assert(v >= 0 && v < m_graph.GetVertex());
		std::vector<int> pathVec;
		Path(v, pathVec);

		for (int i = 0; i < pathVec.size(); i++)
		{
			std::cout << pathVec[i];
			if (i == pathVec.size() - 1)
			{
				std::cout << std::endl;
			}
			else
			{
				std::cout << " -> ";
			}
		}
	}

private:
	void dfs(int v)
	{
		m_bVisitedList[v] = true;

		typename Graph::AdjIterator adj(m_graph, v);
		for (int i = adj.Begin(); !adj.End(); i = adj.Next())
		{
			if (!m_bVisitedList[i])
			{
				m_fromVertexList[i] = v;
				dfs(i);
			}
		}
	}

private:
	Graph &m_graph;
	int m_startVertex;
	bool* m_bVisitedList;
	int* m_fromVertexList;
};
