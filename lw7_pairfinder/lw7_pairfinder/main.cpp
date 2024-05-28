/*
[# 50] Задан двудольный граф 𝐺=𝐺(𝑋,𝐸,𝑌), где 𝑋, 𝑌 – множество вершин,
|𝑋|=|𝑌|=𝑛; 𝐸  – множество ребер. Найти полное паросочетание, 
воспользовавшись алгоритмом Хопкрофта-Карпа.
*/

#include <iostream>
#include "PairFinder.h"

int main()
{
    PairFinder finder(std::cin);

    std::cout << finder.CountPair() << std::endl;
}
