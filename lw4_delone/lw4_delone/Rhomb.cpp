#include "Rhomb.h"
#include <algorithm>
#include <stdexcept>

Rhomb::Rhomb(Edge e, int v1, int v2)
	: m_edge(e), m_v1(v1), m_v2(v2)
{}

void Rhomb::Insert(int v)
{
	if (m_v1 == v || m_v2 == v) 
        return;
    else if (this->Size() == 2)
        throw std::logic_error("Insert in filled rhomb");

	(m_v1 == -1 ? m_v1 : m_v2) = v;
}

void Rhomb::Replace(int u, int v)
{
    if (m_v1 == u) 
        m_v1 = v;
    else if (m_v2 == u) 
        m_v2 = v;
    else 
        Insert(v);
}

int Rhomb::Min() const
{
    if (m_v1 != -1 && m_v2 != -1) 
        return std::min(m_v1, m_v2);
    else if (m_v1 == -1 && m_v2 == -1)
        throw std::logic_error("Get min in empty rhomb");

    return m_v1 != -1 ? m_v1 : m_v2;
}

int Rhomb::Size() const
{
    return (int)(m_v1 != -1) + (int)(m_v2 != -1);
}

bool Rhomb::operator==(const Rhomb& r) const
{
    return m_edge == r.m_edge;
}
