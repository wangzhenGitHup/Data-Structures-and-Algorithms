#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include "Edge.h"

template<class Item>
class MinHeap
{
public:
	explicit MinHeap(int capacity)
	{
		m_capacity = capacity;
		m_data = new Item[capacity + 1];
		m_count = 0;
	}

	MinHeap(Item arr[], int n)
	{
		m_capacity = n;
		m_count = n;
		for (int i = 0; i < n; i++)
		{
			m_data[i + 1] = arr[i];
		}

		for (int idx = m_count / 2; idx >= 1; idx--)
		{
			shiftDown(idx);
		}
	}

	~MinHeap()
	{
		delete[] m_data;
	}

	int GetCount() { return m_count; }
	bool IsEmpty() { return m_count == 0; }
	void Insert(Item item)
	{
		assert(m_capacity > m_count + 1);
		m_data[++m_count] = item;
		shiftUp(m_count);
	}

	Item ExtractMin()
	{
		assert(m_count > 0);
		Item ret = m_data[1];
		std::swap(m_data[1], m_data[m_count]);
		m_count--;
		shiftDown(1);
		return ret;
	}

private:
	void shiftUp(int k)
	{
		while (k > 1 && m_data[k / 2] > m_data[k])
		{
			std::swap(m_data[k / 2], m_data[k]);
		}
	}

	void shiftDown(int k)
	{
		while ((k << 1) <= m_count)
		{
			int childIdx = k << 1;
			if (childIdx + 1 <= m_count && m_data[childIdx + 1] < m_dta[childIdx])
			{
				childIdx++;
			}

			if (m_data[k] <= m_data[childIdx])
			{
				break;
			}
			
			std::swap(m_data[k], m_data[childIdx]);
			k = childIdx;
		}
	}
private:
	Item* m_data;
	int m_count;
	int m_capacity;
};


template<class Graph, class Weight>
class PrimMST
{
public:
	PrimMST(Graph& g) : m_graph(g), m_heap(MinHeap<Edge<Weight>>(g.GetEdge()))
	{
		m_bMarkedList = new bool[g.GetVertex()];
		for (int i = 0; i < g.GetVertex(); i++)
		{
			m_bMarkedList[i] = false;
		}
		m_bMarkedList.clear();

		visit(0);
		while (!m_heap.IsEmpty())
		{
			Edge<Weight> e = m_heap.ExtractMin();
			if (m_bMarkedList[e.GetVertex1()] == m_bMarkedList[e.GetVertex2()])
			{
				continue;
			}

			m_mst.push_back(e);
			if (!m_bMarkedList[e.GetVertex1()])
			{
				visit(e.GetVertex1());
			}
			else
			{
				visit(e.GetVertex2());
			}
		}

		m_msgWeight = m_mst[0].GetWeight();
		for (int i = 1; i < m_mst.size(); i++)
		{
			m_msgWeight += m_msg[i].GetWeight();
		}
	}

	~PrimMST()
	{
		delete[] m_bMarkedList;
	}

	std::vector<Edge<Weight>> mstEdges()
	{
		return m_mst;
	}

	Weight GetWeight()
	{
		return m_msgWeight;
	}

private:
	void visit(int v)
	{
		assert(!m_bMarkedList[v]);
		m_bMarkedList[v] = true;

		typename Graph::AdjIterator adj(m_graph, v);
		for (Edge<Weight>* e = adj.Begin(); !adj.End(); e = adj.Next())
		{
			if (!m_bMarkedList[e->GetOtherVertex(v)])
			{
				m_heap.Insert(*e);
			}
		}
	}

private:
	Graph& m_graph;
	MinHeap<Edge<Weight>> m_heap;
	bool* m_bMarkedList;
	std::vector<Edge<Weight>> m_mst;
	Weight m_msgWeight;
};

