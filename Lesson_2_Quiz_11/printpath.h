#pragma once
#ifndef expand_H
#define expand_H
#include <vector>
class printpath {
public:
	/*
	* Vectors
	*/

	std::vector<std::vector<unsigned int>> grid_;
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
	printpath();

	/*
	* Destructor.
	*/
	~printpath();


	/*
	* Search  printpath error variables given cross track error.
	*/
	std::vector<std::vector<char>> Search();

};



#endif /* expand_H */

