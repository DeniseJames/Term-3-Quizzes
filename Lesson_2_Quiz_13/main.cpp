#include "astar.h"
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	std::vector<std::vector<int>> return_search;
	astar astar;
	return_search = astar.Search();

	cout << "astar matrix is: " << endl;
	for (auto vec : return_search)
	{
		for (auto x : vec)
			std::cout << setw(4) << x;
		std::cout << std::endl;
	}

	return 0;
}

//from Sebastian's Python
//[0, -1, -1, -1, -1, -1]
//[1, -1, -1, -1, -1, -1]
//[2, -1, -1, -1, -1, -1]
//[3, -1, -1, 8, 9, 10]
//[4, 5, 6, 7, -1, 11]


// c++ code
//astar matrix is :

//0 - 1 - 1 - 1 - 1 - 1
//1 - 1 - 1 - 1 - 1 - 1
//2 - 1 - 1 - 1 - 1 - 1
//3 - 1 - 1   8   9  10
//4   5   6   7 - 1  11