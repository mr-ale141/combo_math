#include <fstream>
#include <boost/timer.hpp>
#include <memory>
#include <string>
#include "DoubleSquare.h"

/*
Содержимое файла с грузами:
C11 C12 .. C1N
C21 C22 .. C2N
...
CN1 CN2 .. CNN

Содержимое для файла с расстояниями аналогичен
*/

bool IsCorrectInputData(int argc)
{
	bool isCorrect = argc == 4;
	if (!isCorrect)
	{
		std::cout << "ERROR! Incorrect number of parameters!" << std::endl;
		std::cout << "Correct:" << std::endl;
		std::cout << "-> double_square.exe <N> <cargo.txt> <location.txt>" << std::endl;
	}
	return isCorrect;
}

std::vector<std::vector<int>> GetMatrix(const int N, char* nameFile)
{
	std::ifstream file(nameFile);
	if (!file)
	{
		std::cout << "Can't open the file '" << nameFile << "'" << std::endl;
		exit(1);
	}
	std::vector<std::vector<int>> matrix(N, std::vector<int>(N));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			file >> matrix[i][j];
			file.get();
		}
	}
	return matrix;
}

void PrintMatrix(int N, std::vector<std::vector<int>> matrix, char* name)
{
	std::cout << "------- " << name << std::endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout.width(2);
			std::cout << matrix[i][j] << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << "-------- " << "End" << std::endl;
}

int main(int argc, char* argv[])
{
	boost::timer t;
	t.restart();
	if (!IsCorrectInputData(argc)) return 1;
	int N = std::atoi(argv[1]);
	auto cargoMatrix = GetMatrix(N, argv[2]);
	auto locationMatrix = GetMatrix(N, argv[3]);
	std::vector<int> companyesMin;
	std::vector<int> locationsMin;

	//PrintMatrix(N, cargoMatrix, "Cargo");
	//PrintMatrix(N, locationMatrix, "Location");
	
	unsigned int minR = GetMinR(
		N,
		cargoMatrix,
		locationMatrix,
		companyesMin,
		locationsMin
	);

	std::cout << "Min R = " << minR << std::endl;

	std::cout << "CompanyMin : ";
	for (auto i : companyesMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	std::cout << "LocationMin: ";
	for (auto i : locationsMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;
	
	std::cout << "Duration: ";
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}

