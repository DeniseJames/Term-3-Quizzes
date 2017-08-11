#include "Expand.h"
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	std::vector<std::vector<int>> return_search;
	Expand Expand;
    return_search = Expand.Search();
	
	cout << "expand matrix is: "<< endl;
	for (auto vec : return_search)
	{
		for (auto x : vec)
			std::cout << setw(4) <<x ;
		std::cout << std::endl;
	}
	
	return 0;
}

//from Sebastian's Python
//	[0, 2, -1, 11, 15, 18]
//  [1, 3, 6, 8, 13, 16]
//  [4, 5, -1, 12, -1, 19]
//  [7, 9, -1, 17, -1, 21]
//  [10, 14, -1, 20, -1, 22]

//From my C++ code 
//
//expand matrix is :
//0   2 - 1  11  15  18
//1   3   6   8  13  16
//4   5 - 1  12 - 1  19
//7   9 - 1  17 - 1  21
//10  14 - 1  20 - 1  22