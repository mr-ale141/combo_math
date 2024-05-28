#define CATCH_CONFIG_MAIN
#include "../lw7_pairfinder/PairFinder.h"
#include "../../Catch2/catch.hpp"
#include <sstream>


TEST_CASE("Test from Wiki")
{
    std::stringstream ss("1 1\n1 2\n2 1\n2 5\n3 3\n3 4\n4 1\n4 5\n5 2\n5 4\n");

    try
    {
        PairFinder finder(ss);

        int count = finder.CountPair();

        REQUIRE(5 == count);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        REQUIRE(false);
    }

}