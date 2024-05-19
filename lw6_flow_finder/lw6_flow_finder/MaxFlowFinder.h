#pragma once
#include <list>
#include "Network.h"

class MaxFlowFinder
{
    MaxFlowFinder() : network(nullptr) {}
    ~MaxFlowFinder() = default;

    Network* network;

    std::vector<VertexNumber>   height;
    std::vector<int>            overflow;
    std::vector<size_t>         edgePosition;
    std::list<VertexNumber>     list;

    void InitializePreflow();

    void Push(EdgeNumber edge);

    void Relabel(VertexNumber vertex);

    void Discharge(VertexNumber vertex);

public:
    MaxFlowFinder(MaxFlowFinder const&) = delete;
    MaxFlowFinder(MaxFlowFinder&&) = delete;
    MaxFlowFinder& operator =(MaxFlowFinder const&) = delete;
    MaxFlowFinder& operator =(MaxFlowFinder&&) = delete;

    static MaxFlowFinder& GetInstance();

    int FindMaximumFlow(Network* network);
    void PrintMaxFlowAsMatrix();
};