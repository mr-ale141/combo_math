#define CATCH_CONFIG_MAIN
#include "../lw5_tree_count/TreeCounter.h"
#include "../../Catch2/catch.hpp"
#include <sstream>


TEST_CASE("Test N = 0")
{
	std::stringstream ss("1 2\n1 3\n1 4\n1 5\n2 1\n3 1\n3 4\n4 1\n4 3\n4 5\n5 1\n5 4");

    try
    {
        TreeCounter matrix(ss);

        double countTree = matrix.GetCountTree();
        
        REQUIRE(8 == countTree);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        REQUIRE(false);
    }

}

TEST_CASE("Test tree")
{
    std::stringstream ss("1 2\n1 3\n2 4\n2 5\n3 6");

    try
    {
        TreeCounter matrix(ss);

        double countTree = matrix.GetCountTree();

        REQUIRE(1 == countTree);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        REQUIRE(false);
    }
}

TEST_CASE("Test 5x5 full")
{
    std::stringstream ss("1 2\n1 3\n1 4\n1 5\n2 1\n2 3\n2 4\n2 5\n3 1\n3 2\n3 4\n3 5\n4 1\n4 2\n4 3\n4 5\n5 1\n5 2\n5 3\n5 4");

    try
    {
        TreeCounter matrix(ss);

        double countTree = matrix.GetCountTree();

        REQUIRE(125 == countTree);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        REQUIRE(false);
    }
}


/*
1---2  4---5
|   |  |   |
3---8  6---7
*/
TEST_CASE("Test 2 connectivity components")
{
    std::stringstream ss("1 2\n1 3\n2 1\n2 8\n8 2\n8 3\n3 1\n3 8\n4 5\n4 6\n5 4\n5 7\n7 5\n7 6\n6 7\n6 4\n");

    try
    {
        TreeCounter matrix(ss);

        double countTree = matrix.GetCountTree();

        REQUIRE(0 == countTree);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        REQUIRE(false);
    }
}