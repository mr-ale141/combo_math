#include "TreeCounter.h"

TreeCounter::TreeCounter(std::istream& in)
{
    SetGraph(in);
    SetKirgofMatrix();
}

void TreeCounter::SetGraph(std::istream& in)
{
    std::string str;
    size_t item1{};
    size_t item2{};
    while (std::getline(in, str))
    {
        std::stringstream ss(str);
        if (ss >> item1 && ss >> item2)
        {
            m_graph.insert(std::pair<size_t, size_t>(item1, item2));
            m_items.insert(item1);
            m_items.insert(item2);
        }
        else
        {
            throw std::invalid_argument("Error in input graph");
        }
    }
}

void TreeCounter::SetKirgofMatrix()
{
    m_kirgof = Matrix(
        m_items.size(),
        std::vector<double>(m_items.size(), 0)
    );
    for (size_t y = 0; y < m_items.size(); ++y)
    {
        for (size_t x = y; x < m_items.size(); ++x)
        {
            if (m_graph.contains(std::pair<size_t, size_t>(y + 1, x + 1)))
            {
                m_kirgof[x][y] = -1;
                m_kirgof[y][x] = -1;
                ++m_kirgof[y][y];
                ++m_kirgof[x][x];
            }
        }
    }
}

void TreeCounter::SetMatrix(std::istream& in)
{
    std::string str;
    size_t countLine = 0;
    size_t countItems = 0;
    while (std::getline(in, str))
    {
        countItems = 0;
        std::vector<double> oneLine;
        std::stringstream ss(str);
        double item;
        while (ss >> item)
        {
            oneLine.push_back(item);
            ++countItems;
        }
        m_kirgof.push_back(oneLine);
        ++countLine;
    }
    if (countItems != countLine)
        throw std::invalid_argument("Incorrect input matrix countLine != countItems");
}

Matrix TreeCounter::GetKirgof() const
{
    return m_kirgof;
}

void TreeCounter::PrintMatrix(std::ostream& out, Matrix matrix)
{
    out << std::fixed;
    auto precisionOld = out.precision();
    out.precision(precision);

    size_t size = matrix.size();
    for (auto& itemY : matrix)
    {
        out << '|';
        for (size_t i = 0; i < size; ++i)
        {
            out << std::setw(width) << itemY[i];
            if (i != size - 1)
                out << ',';
        }
        out << '|' << std::endl;
    }

    out.precision(precisionOld);
    out << std::defaultfloat;
}

Matrix TreeCounter::GetMinor_1_1() const
{
    Matrix minor;
    for (size_t y = 1; y < m_items.size(); ++y)
    {
        std::vector<double> vector;
        for (size_t x = 1; x < m_items.size(); ++x)
        {
            vector.push_back(m_kirgof[y][x]);
        }
        minor.push_back(vector);
    }
    return minor;
}

void TreeCounter::AddLine(Matrix& matrix, size_t line)
{
    if (line == 0)
        throw std::invalid_argument("Add line with sub line == -1");

    size_t size = matrix.size();
    for (size_t x = 0; x < size; ++x)
    {
        matrix[line][x] += matrix[line - 1][x];
    }
}

void TreeCounter::AddWithMultiplyLine(Matrix& matrix, size_t line, size_t sumLine, double value)
{
    size_t size = matrix.size();
    for (size_t x = 0; x < size; ++x)
    {
        matrix[line][x] += matrix[sumLine][x] * value;
    }
}

double TreeCounter::GetCountTree() const
{
    Matrix minor = GetMinor_1_1();
    for (size_t y = 1; y < minor.size(); ++y)
    {
        for (size_t x = 0; x < y; ++x)
        {
            double value = minor[y][x];
            if (value == 0)
            {
                continue;
            }
            size_t sub = 1;
            size_t sumLine = y - sub;
            double upValue = minor[sumLine][x];
            if (upValue == 1)
            {
                AddLine(minor, y);
                continue;
            }
            while (upValue == 0)
            {
                ++sub;
                sumLine = (y - sub) % minor.size();
                upValue = minor[sumLine][x];
            }

            AddWithMultiplyLine(minor, y, sumLine, -value / upValue);

            std::cout << "Minor after transformations is" << std::endl;
            PrintMatrix(std::cout, minor);
        }
    }

    double answer = 1.;

    for (size_t i = 0; i < minor.size(); ++i)
        answer *= minor[i][i];
    return answer; // static_cast<int>
}
