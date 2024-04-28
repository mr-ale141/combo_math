#include "Edge.h"

Edge::Edge(int v1, int v2)
	: m_v1(v1), m_v2(v2)
{}

bool Edge::operator==(const Edge& e) const
{
	return m_v1 == e.m_v1
		&& m_v2 == e.m_v2;
}
