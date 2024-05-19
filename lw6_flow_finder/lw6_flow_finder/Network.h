#pragma once
#include <cassert>
#include <vector>
#include <stdexcept>
#include <string>

typedef size_t EdgeNumber;
typedef size_t VertexNumber;

class UnknownEdgeException : public std::out_of_range
{
public:
    explicit UnknownEdgeException(EdgeNumber edgeNumber)
        : std::out_of_range("Edge " + std::to_string(edgeNumber) + " doesn't exist") {}
};

class UnknownVertexException : public std::out_of_range
{
public:
    explicit UnknownVertexException(VertexNumber vertexNumber)
        : std::out_of_range("Vertex " + std::to_string(vertexNumber) + " doesn't exist") {}
};

class FlowMoreThanCapacityException : public std::logic_error
{
public:
    explicit FlowMoreThanCapacityException(EdgeNumber edgeNumber)
        : std::logic_error("Edge " + std::to_string(edgeNumber) + "is overflowed") {}
};


template <typename T>
class Network
{
    struct Edge
    {
        EdgeNumber source;
        EdgeNumber target;

        T capacity;
        T flow;

        Edge(EdgeNumber source, EdgeNumber target, T capacity)
            : source(source), target(target), capacity(capacity), flow(0) {}
        ~Edge() = default;
    };

    VertexNumber flowSource;
    VertexNumber flowTarget;

    std::vector<Edge> edges;
    std::vector<std::vector<EdgeNumber>> graph;
    std::vector<std::vector<EdgeNumber>> graph_reverse;

public:
    Network() = delete;

    explicit Network(size_t numberOfVertices, VertexNumber flowSource, VertexNumber flowTarget)
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

    ~Network() = default;

    size_t numberOfVertices() const
    {
        return graph.size();
    }

    VertexNumber getFlowSource() const
    {
        return flowSource;
    }

    VertexNumber getFlowTarget() const
    {
        return flowTarget;
    }

    const std::vector<EdgeNumber>& edgesFrom(VertexNumber vertexNumber) const
    {
        if (!(vertexNumber < graph.size()))
            throw UnknownVertexException(vertexNumber);

        return graph[vertexNumber];
    }

    const std::vector<EdgeNumber>& edgesTo(VertexNumber vertexNumber) const
    {
        if (!(vertexNumber < graph.size()))
            throw UnknownVertexException(vertexNumber);

        return graph_reverse[vertexNumber];
    }

    EdgeNumber getBackEdge(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return edgeNumber ^ 1;
    }

    VertexNumber getEdgeSource(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return edges[edgeNumber].source;
    }

    VertexNumber getEdgeTarget(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return edges[edgeNumber].target;
    }

    T getEdgeCapacity(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return edges[edgeNumber].capacity;
    }

    T getEdgeFlow(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return edges[edgeNumber].flow;
    }

    T updateEdgeFlow(EdgeNumber edgeNumber, T delta)
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        edges[edgeNumber].flow += delta;
        edges[edgeNumber ^ 1].flow -= delta;

        if (std::abs(edges[edgeNumber].flow) > std::max(edges[edgeNumber].capacity, edges[edgeNumber ^ 1].capacity))
            throw FlowMoreThanCapacityException(edgeNumber);

        return edges[edgeNumber].flow;
    }

    VertexNumber addVertex()
    {
        graph.resize(graph.size() + 1);
        graph_reverse.resize(graph_reverse.size() + 1);
        return graph.size() - 1;
    }

    void addEdge(VertexNumber source, VertexNumber target, T capacity)
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

    bool isBackEdge(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return static_cast<bool>(edgeNumber % 2);
    }

    bool isStraightEdge(EdgeNumber edgeNumber) const
    {
        if (!(edgeNumber < edges.size()))
            throw UnknownEdgeException(edgeNumber);

        return !isBackEdge(edgeNumber);
    }
};