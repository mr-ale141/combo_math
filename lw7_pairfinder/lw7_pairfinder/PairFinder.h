#pragma once
#include <iostream>
#include <vector>
#include <list>

// u - left
// v - right

class PairFinder
{
public:
	PairFinder(std::istream& in);
	int CountPair();

private:
	bool Bfs();
	bool Dfs(int u);
	void AddEdge(int u, int v);
	int m_uSize;
	int m_vSize;
	const int NIL{};
	const int INF = INT_MAX;
	std::vector<std::list<int>> m_adj;
	std::vector<int> m_pairU;
	std::vector<int> m_pairV;
	std::vector<int> m_dist;
};