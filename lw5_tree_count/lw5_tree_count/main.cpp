#include "TreeCounter.h"

int main()
{
    try
    {
        TreeCounter matrix(std::cin);

        Matrix kirgofMatrix = matrix.GetKirgof();
        Matrix minor_1_1 = matrix.GetMinor_1_1();

        std::cout << "Kirgof Matrix is:" << std::endl;
        matrix.PrintMatrix(std::cout, kirgofMatrix);
        std::cout << "Minor_1_1 of kirgof is:" << std::endl;
        matrix.PrintMatrix(std::cout, minor_1_1);

        double countTree = matrix.GetCountTree();
        std::cout << "Count of Tree = " << countTree << std::endl;
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }

}
