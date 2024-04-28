#include "DelaunayParser.h"
#include <algorithm>

const double eps = 1e-9;

namespace
{
	void AddInGraph(std::unordered_set<Rhomb, Rhomb::HashFunc>& graph, Edge e, int item)
	{
		auto rhomb = graph.extract(Rhomb(e));
		if (rhomb)
		{
			rhomb.value().Insert(item);
			graph.insert(std::move(rhomb));
		}
		else
		{
			Rhomb r(e);
			r.Insert(item);
			graph.insert(std::move(r));
		}
	}

	void ReplaceInGraph(std::unordered_set<Rhomb, Rhomb::HashFunc>& graph, Edge e, int target, int src)
	{
		auto rhomb = graph.extract(Rhomb(e));
		if (rhomb)
		{
			rhomb.value().Replace(target, src);
			graph.insert(std::move(rhomb));
		}
		else
		{
			Rhomb r(e);
			r.Replace(target, src);
			graph.insert(std::move(r));
		}
	}
}

Triangulation DelaunayParser::GetTriangulation(std::istream& in)
{
	SetPoints(in);

	if (m_triangulation.points.size() < 3) {
		return m_triangulation;
	}

	m_convexHull[0] = ListEdge{ 1, 1 };
	m_convexHull[1] = ListEdge{ 0, 0 };
	m_triangulation.graph.insert(Rhomb(Edge(0, 1), 2));

	for (int i = 2; i < m_triangulation.points.size(); ++i) {
		AddPointToTriangulation(i);
	}

	return m_triangulation;
}

void DelaunayParser::AddPointToTriangulation(int indexNewPoint)
{
	auto& points = m_triangulation.points;

	// move right check and fix
	int indexHullPoint = indexNewPoint - 1;
	auto lastVector = points[indexHullPoint] - points[indexNewPoint];
	int nextIndexHullPoint = m_convexHull[indexHullPoint].right;
	auto newVector = points[nextIndexHullPoint] - points[indexNewPoint];

	while (CrossProduct(lastVector, newVector) > -eps) {
		FixTriangulation(indexHullPoint, nextIndexHullPoint, indexNewPoint);

		indexHullPoint = nextIndexHullPoint;
		lastVector = newVector;
		nextIndexHullPoint = m_convexHull[indexHullPoint].right;
		newVector = points[nextIndexHullPoint] - points[indexNewPoint];
	}
	m_convexHull[indexNewPoint].right = indexHullPoint;

	// move left check and fix
	indexHullPoint = indexNewPoint - 1;
	lastVector = points[indexHullPoint] - points[indexNewPoint];
	nextIndexHullPoint = m_convexHull[indexHullPoint].left;
	newVector = points[nextIndexHullPoint] - points[indexNewPoint];

	while (CrossProduct(lastVector, newVector) < eps) {
		FixTriangulation(nextIndexHullPoint, indexHullPoint, indexNewPoint);

		indexHullPoint = nextIndexHullPoint;
		lastVector = newVector;
		nextIndexHullPoint = m_convexHull[indexHullPoint].left;
		newVector = points[nextIndexHullPoint] - points[indexNewPoint];
	}
	m_convexHull[indexNewPoint].left = indexHullPoint;

	m_convexHull[m_convexHull[indexNewPoint].right].left = indexNewPoint;
	m_convexHull[indexHullPoint].right = indexNewPoint;

}

void DelaunayParser::FixTriangulation(int left, int right, int outer)
{
	auto& graph = m_triangulation.graph;

	m_stack[0] = Edge{ left, right };
	int stackSize = 1;
	while (stackSize > 0) {
		left = m_stack[stackSize - 1].m_v1;
		right = m_stack[stackSize - 1].m_v2;
		--stackSize;

		// Берем минимум в множестве, потому что outer > индекса любой добавленной точки
		auto iter = graph.find(Rhomb(Edge{ std::min(left, right), std::max(left, right) }));
		int inner = (*iter).Min();

		if (CheckDelaunayCondition(left, right, outer, inner)) {
			// Если менять ничего в четырехугольнике не надо,
			// просто добавляем недостающие ребра и выходим
			AddInGraph(graph, Edge{ right, outer }, left);
			AddInGraph(graph, Edge{ left, outer }, right);
			if (right < left) std::swap(right, left);
			AddInGraph(graph, Edge{ left, right }, outer);
			continue;
		}

		// Иначе перестраиваем триангуляцию в четырехугольнике
		ReplaceInGraph(graph, Edge{ right, outer }, left, inner);
		ReplaceInGraph(graph, Edge{ left, outer }, right, inner);
		ReplaceInGraph(graph, Edge{ std::min(inner, left), std::max(inner, left) }, right, outer);
		ReplaceInGraph(graph, Edge{ std::min(inner, right), std::max(inner, right) }, left, outer);

		graph.erase(Rhomb(Edge{ std::min(left, right), std::max(left, right) }));

		// И добавляем 2 новых рекурсивных вызова
		m_stack[stackSize++] = Edge{ left, inner };
		m_stack[stackSize++] = Edge{ inner, right };
	}
}

bool DelaunayParser::CheckDelaunayCondition(int left, int right, int outer, int inner) const
{
	const auto& l = m_triangulation.points[left];
	const auto& r = m_triangulation.points[right];
	const auto& t = m_triangulation.points[outer];
	const auto& b = m_triangulation.points[inner];

	// Проверка на то, что подан четырехугольник
	if (outer == inner) {
		return true;
	}

	// Проверка на выпуклость
	if (CrossProduct(l - t, b - t) < 0 || CrossProduct(r - t, b - t) > 0) {
		return true;
	}

	// Проверка условия Делоне, как в книге из статьи
	const auto Sa = (t.m_x - r.m_x) * (t.m_x - l.m_x) + (t.m_y - r.m_y) * (t.m_y - l.m_y);
	const auto Sb = (b.m_x - r.m_x) * (b.m_x - l.m_x) + (b.m_y - r.m_y) * (b.m_y - l.m_y);
	if (Sa > -eps && Sb > -eps) {
		return true;
	}
	if (!(Sa < 0 && Sb < 0)) {
		auto Sc = CrossProduct(t - r, t - l);
		auto Sd = CrossProduct(b - r, b - l);
		if (Sc < 0) Sc = -Sc;
		if (Sd < 0) Sd = -Sd;
		if (Sc * Sb + Sa * Sd > -eps) {
			return true;
		}
	}
	return false;
}

void DelaunayParser::SetPoints(std::istream& in)
{
	Vector2D v;
	while ((std::cin >> v.m_x) && (std::cin >> v.m_y)) {
		m_triangulation.points.push_back(v);
	}

	m_stack.resize(m_triangulation.points.size());
	m_convexHull.resize(m_triangulation.points.size());

	std::sort(
		m_triangulation.points.begin(), 
		m_triangulation.points.end(), 
		[](auto& lhs, auto& rhs) {
			return lhs.m_x < rhs.m_x;
		}
	);
}
