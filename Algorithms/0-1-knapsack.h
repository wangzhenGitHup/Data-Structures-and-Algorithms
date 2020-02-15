#pragma once

#include <vector>
#include <cassert>

class Knapsack01
{
public:
	int knapsack01(const std::vector<int>& w, const std::vector<int>& v, int c)
	{
		int n = w.size();
		m_memo = std::vector<std::vector<int>>(n, std::vector<int>(c + 1, -1));
		return bestvalue(w, v, n - 1, c);
	}

private:
	int bestvalue(const std::vector<int>& w, const std::vector<int> v, int index, int c)
	{
		if (index < 0 || c <= 0)
		{
			return 0;
		}

		if (m_memo[index][c] != -1)
		{
			return m_memo[index][c];
		}

		int res = bestvalue(w, v, index - 1, c);
		if (c >= w[index])
		{
			res = max2(res, v[index] + bestvalue(w, v, index - 1, c - w[index]));
		}
		m_memo[index][c] = res;

		return res;
	}

	int max2(int a, int b)
	{
		return a > b ? a : b;
	}

private:
	std::vector<std::vector<int>> m_memo;
};