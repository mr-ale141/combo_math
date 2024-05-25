#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <exception>
#include <iomanip>
#include <cmath>
#include <set>

const int precision = 2;
const int width = 6;

using Matrix = std::vector<std::vector<double>>;

class TreeCounter
{
public:
    TreeCounter(std::istream& in);
    static void PrintMatrix(std::ostream& out, Matrix matrix);
    double GetCountTree() const;
    Matrix GetKirgof() const;
    Matrix GetMinor() const;
private:
    static bool SwapColumn(Matrix& minor, size_t x);
    static void AddLine(Matrix& matrix, size_t y);
    static void AddWithMultiplyLine(Matrix& matrix, size_t line, size_t sumLine, double value);
    void SetMatrix(std::istream& in);
    void SetGraph(std::istream& in);
    void SetKirgofMatrix();
    Matrix m_kirgof;
    std::set<std::pair<size_t, size_t>> m_graph;
    std::set<size_t> m_items;
};
