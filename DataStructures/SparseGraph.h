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

private:
	int m_vertex; //节点
	int m_edge; //边
	bool m_bDirected; //是否是有向图
	std::vector<std::vector<int>> m_graph;
};
