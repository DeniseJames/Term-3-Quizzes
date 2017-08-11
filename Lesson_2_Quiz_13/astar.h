#pragma once
#pragma once
#ifndef astar_H
#define astar_H
#include <vector>
class astar {
public:
	/*
	* Vectors
	*/

	std::vector<std::vector<unsigned int>> grid_;
	std::vector<std::vector<unsigned int>> heuristics_;
	std::vector<unsigned int> goal_;
	std::vector<unsigned int> init_;
	int cost_;
	std::vector<std::vector<int>> delta_;
	std::vector<std::vector<unsigned int>> closed_;
	std::vector<std::vector<int>> expand_;
	std::vector<std::vector<int>> action_;
	std::vector<std::vector<char>> policy_;
	std::vector<std::vector<char>> delta_name_;
	/*
	* Constructor
	*/
	astar();

	/*
	* Destructor.
	*/
	~astar();


	/*
	* Search  astar error variables given cross track error.
	*/
	std::vector<std::vector<int>> Search();

};



#endif /* astar_H */

