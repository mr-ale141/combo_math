#pragma once
#include <list>
#include "Network.h"
/*
Алгоритм поднять-в-начало:
    - занести все v э V | {s, t} (кроме исток и сток) в односвязный список
    - пройдемся по списку и выполним DISCHARGE от каждой вершины
        - при этом, если в результате DISCHARGE(v) R(v) увеличилось,
            то поместим v в начало списка и начнем заново
        - если дошли до конца, то завершаем работу

*/

template <typename T>
class MaxFlowFinder
{
    MaxFlowFinder() : network(nullptr) {}
    ~MaxFlowFinder() = default;

    Network<T>* network;

    std::vector<VertexNumber>   height;
    std::vector<T>              overflow;
    std::vector<size_t>         edgePosition;
    std::list<VertexNumber>     list;

    void initializePreflow()
    {
        height.resize(network->numberOfVertices());
        overflow.resize(network->numberOfVertices());
        edgePosition.resize(network->numberOfVertices());

        height.assign(height.size(), 0);
        height[network->getFlowSource()] = network->numberOfVertices();

        overflow.assign(overflow.size(), 0);
        for (VertexNumber vertex = 0; vertex < network->numberOfVertices(); ++vertex)
        {
            for (EdgeNumber edge : network->edgesFrom(vertex))
            {
                network->updateEdgeFlow(edge, -network->getEdgeFlow(edge));
            }
        }
        for (EdgeNumber edge : network->edgesFrom(network->getFlowSource()))
        {
            network->updateEdgeFlow(edge, network->getEdgeCapacity(edge));
            overflow[network->getEdgeTarget(edge)] += network->getEdgeCapacity(edge);
            overflow[network->getFlowSource()] -= network->getEdgeCapacity(edge);
        }

        edgePosition.assign(edgePosition.size(), 0);

        list.clear();
        for (VertexNumber vertex = 0; vertex < network->numberOfVertices(); ++vertex)
        {
            if (vertex != network->getFlowSource() && vertex != network->getFlowTarget())
            {
                list.push_back(vertex);
            }
        }
    }

    void push(EdgeNumber edge)
    {
        VertexNumber from = network->getEdgeSource(edge);
        VertexNumber to = network->getEdgeTarget(edge);

        assert(overflow[from] > 0);
        assert(network->getEdgeCapacity(edge) - network->getEdgeFlow(edge));
        assert(height[from] == 1 + height[to]);

        T delta = std::min(network->getEdgeCapacity(edge) - network->getEdgeFlow(edge), overflow[from]);
        network->updateEdgeFlow(edge, delta);
        overflow[from] -= delta;
        overflow[to] += delta;
    }

    void relabel(VertexNumber vertex)
    {
        VertexNumber minimumHeight = height[vertex];

        for (EdgeNumber edge : network->edgesFrom(vertex))
        {
            if (!(network->getEdgeCapacity(edge) - network->getEdgeFlow(edge)))
            {
                continue;
            }
            VertexNumber to = network->getEdgeTarget(edge);
            assert(height[to] >= height[vertex]);
            minimumHeight = std::min(minimumHeight, height[to]);
        }

        height[vertex] = 1 + minimumHeight;
    }

    void discharge(VertexNumber vertex)
    {
        while (overflow[vertex] > 0)
        {
            if (edgePosition[vertex] >= network->edgesFrom(vertex).size())
            {
                relabel(vertex);
                edgePosition[vertex] = 0;
                continue;
            }

            EdgeNumber edge = network->edgesFrom(vertex)[edgePosition[vertex]];
            VertexNumber to = network->getEdgeTarget(edge);
            if (network->getEdgeCapacity(edge) - network->getEdgeFlow(edge)
                && height[vertex] == 1 + height[to])
            {
                push(edge);
            }
            else
            {
                ++edgePosition[vertex];
            }
        }
    }

public:
    MaxFlowFinder(MaxFlowFinder const&) = delete;
    MaxFlowFinder(MaxFlowFinder&&) = delete;
    MaxFlowFinder& operator =(MaxFlowFinder const&) = delete;
    MaxFlowFinder& operator =(MaxFlowFinder&&) = delete;

    static MaxFlowFinder& getInstance()
    {
        static MaxFlowFinder instance;
        return instance;
    }

    T findMaximumFlow(Network<T>* network)
    {
        this->network = network;

        initializePreflow();

        auto listIterator = list.begin();
        while (listIterator != list.end())
        {
            VertexNumber vertex = *listIterator;
            VertexNumber previousHeight = height[vertex];

            discharge(vertex);

            if (height[vertex] > previousHeight)
            {
                list.erase(listIterator);
                list.push_front(vertex);
                listIterator = list.begin();
            }
            else
            {
                ++listIterator;
            }
        }

        return -overflow[network->getFlowSource()];
    }

};