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

private:
	int m_vertex; //�ڵ�
	int m_edge; //��
	bool m_bDirected; //�Ƿ�������ͼ
	std::vector<std::vector<int>> m_graph;
};
