#pragma once
#include <unordered_set>
#include "Edge.h"

class Rhomb
{
public:
	Rhomb(Edge e, int v1 = -1, int v2 = -1);

	Edge m_edge;
	int m_v1;
	int m_v2;

	void Insert(int v);
	void Replace(int u, int v);
	int Min() const;
	int Size() const;
	bool operator==(const Rhomb& r) const;

	struct HashFunc
	{
		size_t operator()(const Rhomb& r) const
		{
			size_t xHash = std::hash<int>()(r.m_edge.m_v1);
			size_t yHash = std::hash<int>()(r.m_edge.m_v2) << 1;
			return xHash ^ yHash;
		}
	};
};
