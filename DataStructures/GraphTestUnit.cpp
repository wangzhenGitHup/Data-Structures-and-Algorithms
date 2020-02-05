// DataTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<ctime>
#include"DenseGraph.h"
#include "SparseGraph.h"

int main()
{
    std::cout << "Hello World!\n";

	int N = 20;
	int M = 100;
	srand(time(NULL));

	SparseGraph g(N, false);
	for (int i = 0; i < M; i++)
	{
		int a = rand() % N;
		int b = rand() % N;
		g.CreateEdge(a, b);
	}

	for (int v = 0; v < N; v++)
	{
		std::cout << v << ": ";
		SparseGraph::AdjIterator adj(g, v);
		for (int j = adj.Begin(); !adj.End(); j = adj.Next())
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "===============================================" << std::endl;


	DenseGraph g2(N, false);
	for (int i = 0; i < M; i++)
	{
		int a = rand() % N;
		int b = rand() % N;
		g2.CreateEdge(a, b);
	}

	for (int v = 0; v < N; v++)
	{
		std::cout << v << " : ";
		DenseGraph::AdjIterator adj(g2, v);
		for (int j = adj.Begin(); !adj.End(); j = adj.Next())
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
