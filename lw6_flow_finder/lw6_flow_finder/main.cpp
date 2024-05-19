/*
[# 100] Для орграфа 𝐺 = (𝑉, 𝐸) требуется найти максимальный поток алгоритмом «поднять-в-начало».
Ввести класс сети.
Пропускная способность задаётся матрицей 𝑛×𝑛, где
источник – вершина с номером 0.
приёмник – вершина с номером 𝑛−1.
Максимальный поток вывести матрицей 𝑛×𝑛.
*/
#include <iostream>
#include "MaxFlowFinder.h"

int main()
{
    size_t numberOfVertices;
    size_t numberOfEdges;
    VertexNumber start;
    VertexNumber finish;

    std::cin >> numberOfVertices >> numberOfEdges >> start >> finish;

    Network network(numberOfVertices, start, finish);

    for (size_t i = 0; i < numberOfEdges; ++i)
    {
        VertexNumber from; // 0 ... numberOfVertices - 1
        VertexNumber to; // 0 ... numberOfVertices - 1
        int capacity;

        std::cin >> from >> to >> capacity;
        network.AddEdge(from, to, capacity);
    }

    auto& finder = MaxFlowFinder::GetInstance();

    int maximumFlow = finder.FindMaximumFlow(&network);

    finder.PrintMaxFlowAsMatrix();

    std::cout << "Max flow = " << maximumFlow;

    return 0;
}
