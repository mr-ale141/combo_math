#pragma once
#include <cassert>
#include <iostream>
#include <set>
#include <iomanip>
#include "Network.h"

using Matrix = std::vector<std::vector<int>>;
const int width = 3;

namespace
{
    void PrintMatrix(std::ostream& out, Matrix matrix)
    {
        std::cout << "   ";
        for (int i = 0; i < matrix.size(); ++i)
            std::cout << std::setw(4) << i;
        std::cout << std::endl;
        std::cout << "   ";
        for (int i = 0; i < matrix.size(); ++i)
            std::cout << "----";
        std::cout << std::endl;

        size_t size = matrix.size();
        int count = 0;
        for (auto& itemY : matrix)
        {
            out << std::setw(3) << count << '|';
            for (size_t i = 0; i < size; ++i)
            {
                if (itemY[i])
                    out << std::setw(width) << itemY[i];
                else
                    out << std::setw(width) << '-';
                if (i != size - 1)
                    out << '|';
            }
            out << '|' << std::endl;
            ++count;
        }
        std::cout << "   ";
        for (int i = 0; i < matrix.size(); ++i)
            std::cout << "----";
        std::cout << std::endl;
    }
}


Network::Network(size_t numberOfVertices, VertexNumber flowSource, VertexNumber flowTarget)
    : flowSource(flowSource), flowTarget(flowTarget)
{
    if (!numberOfVertices)
        throw UnknownVertexException(flowSource);
    if (!(flowSource < numberOfVertices))
        throw UnknownVertexException(flowSource);
    if (!(flowTarget < numberOfVertices))
        throw UnknownVertexException(flowTarget);

    graph.resize(numberOfVertices);
    graph_reverse.resize(numberOfVertices);
}

size_t Network::NumberOfVertices() const
{
    return graph.size();
}

VertexNumber Network::GetFlowSource() const
{
    return flowSource;
}

VertexNumber Network::GetFlowTarget() const
{
    return flowTarget;
}

const std::vector<EdgeNumber>& Network::EdgesFrom(VertexNumber vertexNumber) const
{
    if (!(vertexNumber < graph.size()))
        throw UnknownVertexException(vertexNumber);

    return graph[vertexNumber];
}

const std::vector<EdgeNumber>& Network::EdgesTo(VertexNumber vertexNumber) const
{
    if (!(vertexNumber < graph.size()))
        throw UnknownVertexException(vertexNumber);

    return graph_reverse[vertexNumber];
}

EdgeNumber Network::GetBackEdge(EdgeNumber edgeNumber) const
{
    if (!(edgeNumber < edges.size()))
        throw UnknownEdgeException(edgeNumber);

    return edgeNumber ^ 1;
}

VertexNumber Network::GetEdgeSource(EdgeNumber edgeNumber) const
{
    if (!(edgeNumber < edges.size()))
        throw UnknownEdgeException(edgeNumber);

    return edges[edgeNumber].source;
}

VertexNumber Network::GetEdgeTarget(EdgeNumber edgeNumber) const
{
    if (!(edgeNumber < edges.size()))
        throw UnknownEdgeException(edgeNumber);

    return edges[edgeNumber].target;
}

int Network::GetEdgeCapacity(EdgeNumber edgeNumber) const
{
    if (!(edgeNumber < edges.size()))
        throw UnknownEdgeException(edgeNumber);

    return edges[edgeNumber].capacity;
}

int Network::GetEdgeFlow(EdgeNumber edgeNumber) const
{
    if (!(edgeNumber < edges.size()))
        throw UnknownEdgeException(edgeNumber);

    return edges[edgeNumber].flow;
}

int Network::UpdateEdgeFlow(EdgeNumber edgeNumber, int delta)
{
    if (!(edgeNumber < edges.size()))
        throw UnknownEdgeException(edgeNumber);

    edges[edgeNumber].flow += delta;
    edges[edgeNumber ^ 1].flow -= delta;

    if (std::abs(edges[edgeNumber].flow) > std::max(edges[edgeNumber].capacity, edges[edgeNumber ^ 1].capacity))
        throw FlowMoreThanCapacityException(edgeNumber);

    return edges[edgeNumber].flow;
}

VertexNumber Network::AddVertex()
{
    graph.resize(graph.size() + 1);
    graph_reverse.resize(graph_reverse.size() + 1);
    return graph.size() - 1;
}

void Network::AddEdge(VertexNumber source, VertexNumber target, int capacity)
{
    if (!(source < graph.size()))
        throw UnknownVertexException(source);
    if (!(target < graph.size()))
        throw UnknownVertexException(target);
    assert(capacity >= 0);

    edges.emplace_back(source, target, capacity);
    edges.emplace_back(target, source, 0);
    graph[source].push_back(edges.size() - 2);
    graph[target].push_back(edges.size() - 1);
    graph_reverse[source].push_back(edges.size() - 1);
    graph_reverse[target].push_back(edges.size() - 2);
}

void Network::PrintEdgesAsMatrix()
{
    Matrix matrix(NumberOfVertices(), std::vector<int>(NumberOfVertices(), 0));
    for (auto& edge : edges)
    {
        if (edge.capacity <= 0)
            continue;
        matrix[edge.source][edge.target] = edge.flow;
    }
    PrintMatrix(std::cout, matrix);
}