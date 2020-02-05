#pragma once

#include<vector>

/*
	����ͼ
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
	int m_vertex; //�ڵ�
	int m_edge; //��
	bool m_bDirected; //�Ƿ�������ͼ
	std::vector<std::vector<bool>> m_graph;
};