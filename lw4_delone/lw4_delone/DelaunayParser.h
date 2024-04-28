#pragma once
#include <unordered_set>
#include <iostream>
#include "Vector2D.h"
#include "Rhomb.h"

struct Triangulation
{
	std::unordered_set<Rhomb, Rhomb::HashFunc> graph;
	std::vector<Vector2D> points;
};

struct ListEdge
{
	int left;
	int right;
};

class DelaunayParser
{
public:
	DelaunayParser() = default;
	Triangulation GetTriangulation(std::istream& in);
private:
	Triangulation m_triangulation;
	std::vector<Edge> m_stack;
	std::vector<ListEdge> m_convexHull;

	void AddPointToTriangulation(int index);
	void FixTriangulation(int left, int right, int outer);
	bool CheckDelaunayCondition(int left, int right, int outer, int inner) const;
	void SetPoints(std::istream& in);

	static double CrossProduct(const Vector2D& lhs, const Vector2D& rhs)
	{
		return lhs.m_x * rhs.m_y - lhs.m_y * rhs.m_x;
	}
};
