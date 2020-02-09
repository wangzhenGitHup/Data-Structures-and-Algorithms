#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

template<class Graph, class Weight>
class ReadGraph2
{
public:
	ReadGraph2(Graph& g, const std::string& fileName)
	{
		std::ifstream file(fileName);
		std::string line;
		int vertex, edge;

		assert(file.is_open());
		assert(getline(file, line));

		std::stringstream ss(line);
		ss >> vertex >> edge;

		assert(vertex == g.GetVertex());

		for (int i = 0; i < edge; i++)
		{
			assert(getline(file, line));
			std::stringstream ss(line);

			int v1, v2;
			Weight w;
			ss >> v1 >> v2 >> w;
			assert(v1 >= 0 && v1 < vertex);
			assert(v2 >= 0 && v2 < vertex);

			g.CreateEdge(v1, v2, w);
		}

	}
};
