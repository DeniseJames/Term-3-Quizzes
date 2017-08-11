#include "printpath.h"
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	std::vector<std::vector<char>> return_search;
	printpath printpath;
	return_search = printpath.Search();

	cout << "printpath matrix is: " << endl;
	for (auto vec : return_search)
	{
		for (auto x : vec)
			std::cout << setw(4) << x;
		std::cout << std::endl;
	}

	return 0;
}

//from Sebastian's Python
