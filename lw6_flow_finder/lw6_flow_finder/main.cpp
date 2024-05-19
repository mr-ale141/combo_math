#include <iostream>
#include "MaxFlowFinder.h"

int main()
{
    size_t numberOfVertices;
    size_t numberOfEdges;
    VertexNumber start;
    VertexNumber finish;

    std::cin >> numberOfVertices >> numberOfEdges >> start >> finish;

    Network<int> network(numberOfVertices, start, finish);

    for (size_t i = 0; i < numberOfEdges; ++i)
    {
        VertexNumber from; // 0 ... numberOfVertices - 1
        VertexNumber to; // 0 ... numberOfVertices - 1
        int capacity;

        std::cin >> from >> to >> capacity;
        network.addEdge(from, to, capacity);
    }

    auto& finder = MaxFlowFinder<int>::getInstance();

    int maximumFlow = finder.findMaximumFlow(&network);

    std::cout << maximumFlow;

    return 0;
}
