#pragma once

#include<vector>

/*
	稠密图
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

private:
	int m_vertex; //节点
	int m_edge; //边
	bool m_bDirected; //是否是有向图
	std::vector<std::vector<bool>> m_graph;
};