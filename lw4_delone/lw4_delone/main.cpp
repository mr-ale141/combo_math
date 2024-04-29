#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include "DelaunayParser.h"

// C:\IPS\combo_math\img2points\img2points\out\build\x64-debug\img2points\img2points.exe

const std::string fileName = "triangulation.html";
std::ofstream file(fileName);
const int width = 800;
const int height = 600;

struct Line
{
	int from;
	int to;

	bool operator==(const Line& l) const
	{
		return (from == l.from) && (to == l.to) || (to == l.from) && (from == l.to);
	}

	struct HashFunc
	{
		size_t operator()(const Line& l) const
		{
			size_t xHash = std::hash<int>()(l.from);
			size_t yHash = std::hash<int>()(l.to) << 1;
			return xHash ^ yHash;
		}
	};
};

std::unordered_set<Line, Line::HashFunc> lines;

void WriteHeader()
{
	file
		<< "<svg xmlns=\"http://www.w3.org/2000/svg\" width='"
		<< width
		<< "' height='"
		<< height
		<< "'>\n";
}

void WriteFooter()
{
	file << "</svg>\n";
}

void DrawLine(const std::vector<Vector2D>& points, Line& line)
{
	Line swapLine(line.to, line.from);

	if (lines.contains(line) || lines.contains(swapLine))
		return;

	lines.insert(line);

	file << '\t'
		<< "<line x1 = '"
		<< points[line.from].m_x
		<< "' y1 = '"
		<< points[line.from].m_y
		<< "' x2 = '"
		<< points[line.to].m_x
		<< "' y2 = '"
		<< points[line.to].m_y
		<< "' stroke = '#000000'"
		<< " />\n";
}

void DrawRhomb(const std::vector<Vector2D>& points, const Rhomb& rhomb)
{
	Line l1{ rhomb.m_edge.m_v1, rhomb.m_edge.m_v2 };
	DrawLine(points, l1);

	Line l2{ rhomb.m_edge.m_v1, rhomb.m_v1 };
	DrawLine(points, l2);

	Line l4{ rhomb.m_edge.m_v2, rhomb.m_v1 };
	DrawLine(points, l4);

	if (rhomb.m_v2 < 0)
		return;

	Line l3{ rhomb.m_edge.m_v1, rhomb.m_v2 };
	DrawLine(points, l3);

	Line l5{ rhomb.m_edge.m_v2, rhomb.m_v2 };
	DrawLine(points, l5);
}

int main()
{
    DelaunayParser parser;

    auto triangulation = parser.GetTriangulation(std::cin);
	auto& graph = triangulation.graph;
	std::vector<Vector2D>& points = triangulation.points;

    WriteHeader();
	for (auto& rhomb : graph)
		DrawRhomb(points, rhomb);
	WriteFooter();
}
