#ifndef Expand_H
#define Expand_H
#include <vector>
class Expand {
public:
	/*
	* Vectors
	*/
	
	std::vector<std::vector<unsigned int>> grid_ ;
	std::vector<unsigned int> goal_;
	std::vector<unsigned int> init_;
	int cost_;
	std::vector<std::vector<int>> delta_;
	std::vector<std::vector<unsigned int>> closed_;
	std::vector<std::vector<int>> expand_;

	
	/*
	* Constructor
	*/
	Expand();

	/*
	* Destructor.
	*/
	~Expand();

	
	/*
	* Search  Expand error variables given cross track error.
	*/
	std::vector<std::vector<int>> Search();

};

#endif /* Expand_H */

