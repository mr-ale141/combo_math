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
        
        REQUIRE(countTree == 8.);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        REQUIRE(false);
    }

}