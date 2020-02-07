#pragma once

#include <cassert>
#include <queue>
#include <vector>
#include <stack>

template<class Graph>
class BFS_Path
{
public:
	BFS_Path(Graph& g, int start) : m_graph(g)
	{
		assert(start >= 0 && start < g.GetVertex());

		m_bVisitedList = new bool[g.GetVertex()];
		m_fromVertexList = new int[g.GetVertex()];
		m_startVertex = start;

		for (int i = 0; i < g.GetVertex(); i++)
		{
			m_bVisitedList[i] = false;
			m_fromVertexList[i] = -1;
			m_orderVertexList[i] = -1;
		}

		bfs();
	}

	~BFS_Path()
	{
		delete[] m_bVisitedList;
		delete[] m_fromVertexList;
		delete[] m_orderVertexList;
	}

	bool HasPath(int v)
	{
		assert(v >= 0 && v < m_graph.GetVertex());
		return m_bVisitedList[v];
	}

	void Path(int v, std::vector<int>& pathVec)
	{
		assert(v >= 0 && v < m_graph.GetVertex());

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

	int GetShortestLength(int v)
	{
		assert(v >= 0 && v < m_graph.GetVertex());
		return m_orderVertexList[v];
	}

private:
	void bfs()
	{
		std::queue<int> pathQueue;
		pathQueue.push(m_startVertex);
		m_bVisitedList[m_startVertex] = true;
		m_orderVertexList[m_startVertex] = 0;
		while (!pathQueue.empty())
		{
			int tmpV = pathQueue.front();
			pathQueue.pop();

			typename Graph::AdjIterator adj(m_graph, tmpV);
			for (int i = adj.Begin(); !adj.End(); i = adj.Next())
			{
				if (!m_bVisitedList[i])
				{
					pathQueue.push(i);
					m_bVisitedList[i] = true;
					m_fromVertexList[i] = tmpV;
					m_orderVertexList[i] = m_orderVertexList[tmpV] + 1;
				}
			}
		}
	}
private:
	Graph& m_graph;
	int m_startVertex;
	bool* m_bVisitedList;
	int* m_fromVertexList;
	int* m_orderVertexList;
};