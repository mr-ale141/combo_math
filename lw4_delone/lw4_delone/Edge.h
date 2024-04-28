#pragma once

class Edge
{
public:
	explicit Edge(int v1 = -1, int v2 = -1);
	int m_v1;
	int m_v2;
	bool operator==(const Edge& e) const;
};
