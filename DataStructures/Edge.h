#pragma once

#include <iostream>
#include <cassert>


template<class Weight>
class Edge
{
public:
	Edge(){}
	
	Edge(int v1, int v2, Weight w)
	{
		m_vertex_1 = v1;
		m_vertex_2 = v2;
		m_weight = w;
	}

	~Edge()
	{

	}

	int GetVertex1() { return m_vertex_1; }
	int GetVertex2() { return m_vertex_2; }
	Weight GetWeight() { return m_weight; }
	int GetOtherVertex(int v)
	{
		assert(v == m_vertex_1 || v == m_vertex_2);
		return (v == m_vertex_1) ? m_vertex_2 : m_vertex_1;
	}

	friend std::ostream& operator<<(std::ostream& os, const Edge& e)
	{
		os << e.m_vertex_1 << "-" << e.m_vertex_2 << " : " << e.m_weight;
		return os;
	}

	bool operator<(Edge<Weight>& e)
	{
		return m_weight < e.GetWeight();
	}

	bool operator<=(Edge<Weight>& e)
	{
		return m_weight <= e.GetWeight()
	}

	bool operator>(Edge<Weight>& e)
	{
		return m_weight > e.GetWeight();
	}

	bool operator>=(Edge<Weight>& e)
	{
		return m_weight >= e.GetWeight();
	}

	bool operator==(Edge<Weight>& e)
	{
		return m_weight == e.GetWeight();
	}

private:
	int m_vertex_1;
	int m_vertex_2;
	Weight m_weight;
};