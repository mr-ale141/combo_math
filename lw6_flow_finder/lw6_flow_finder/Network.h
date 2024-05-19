#pragma once
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

class Network
{
    struct Edge
    {
        EdgeNumber source;
        EdgeNumber target;

        int capacity;
        int flow;

        Edge(EdgeNumber source, EdgeNumber target, int capacity)
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
    explicit Network(size_t numberOfVertices, VertexNumber flowSource, VertexNumber flowTarget);
    ~Network() = default;
    size_t NumberOfVertices() const;
    VertexNumber GetFlowSource() const;
    VertexNumber GetFlowTarget() const;
    const std::vector<EdgeNumber>& EdgesFrom(VertexNumber vertexNumber) const;
    const std::vector<EdgeNumber>& EdgesTo(VertexNumber vertexNumber) const;
    EdgeNumber GetBackEdge(EdgeNumber edgeNumber) const;
    VertexNumber GetEdgeSource(EdgeNumber edgeNumber) const;
    VertexNumber GetEdgeTarget(EdgeNumber edgeNumber) const;
    int GetEdgeCapacity(EdgeNumber edgeNumber) const;
    int GetEdgeFlow(EdgeNumber edgeNumber) const;
    int UpdateEdgeFlow(EdgeNumber edgeNumber, int delta);
    VertexNumber AddVertex();
    void AddEdge(VertexNumber source, VertexNumber target, int capacity);
    void PrintEdgesAsMatrix();
};
