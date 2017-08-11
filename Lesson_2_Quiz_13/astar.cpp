#include "astar.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

astar::astar() : grid_({
	{0, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0}})
	, heuristics_({
	{9, 8, 7, 6, 5, 4},
	{8, 7, 6, 5, 4, 3},
	{7, 6, 5, 4, 3, 2},
	{6, 5, 4, 3, 2, 1},
	{5, 4, 3, 2, 1, 0}} )
	, goal_({4, 5})
	, init_({ 0,0 })
	, cost_(1)
	, delta_({ {-1, 0 },    //go up
			   { 0,-1 },    //go left
			   { 1, 0 },    //go down
			   { 0, 1 } })  //go right 
{}

astar::~astar() {}

std::vector<std::vector<int>> astar::Search() {
	for (unsigned int i = 0; i < grid_.size(); i++) {
		vector<unsigned int> temp;
		for (unsigned int j = 0; j < grid_[0].size(); j++) {
			temp.push_back(0);
		}

		closed_.push_back(temp);
	}
	// Set the closed corresponding starting position
	closed_[init_[0]][init_[1]] = 1;
	// now define the expand vector
	for (unsigned int i = 0; i < grid_.size(); i++) {
		vector<int> temp;
		for (unsigned int j = 0; j < grid_[0].size(); j++) {
			temp.push_back(-1);
		}
		expand_.push_back(temp);
	}

	// Initialize x, y to starting grid position	
	int x = init_[0];
	int y = init_[1];
	int g = 0;
	int h = heuristics_[x][y];
	int	f = h + g;
	
	// Declare and define an open 2-D matrix called open
	// one row, five elements in the row initialized to 0
	vector<vector<int>> open(1, vector<int>(5, 0));
	// f is first for sorting
	open = { { f, g, h, x, y } };
	int count = 0;
	bool found = false; // set when search is complete
	bool resign = false; // set if we cannot expand

	while (found == false && resign == false) {
		if (open.size() == 0) {
			resign = true;
		}
		else {
			sort(open.begin(), open.end());
			reverse(open.begin(), open.end());
			std::vector<int> next = open.back();
			open.pop_back();
			
			int f = next[0];
			int g = next[1];
			int h = next[2];
			int x = next[3];
			int y = next[4];

			expand_[x][y] = count;
			count += 1;
			//cout << "goal_[0] is " << goal_[0] << "goal_[1] is " << goal_[1];
			if (x == goal_[0] && y == goal_[1]) {
				found = true;
			}
			else {
				for (unsigned int i = 0; i < delta_.size(); i++) {
					int x2 = x + delta_[i][0];
					int y2 = y + delta_[i][1];
					if (x2 >= 0 && x2 < grid_.size() && y2 >= 0 && y2 < grid_[0].size()) {
						if (closed_[x2][y2] == 0 && grid_[x2][y2] == 0) {
							int g2 = g + cost_;
							int h2 = heuristics_[x2][y2];
							int	f2 = g2 + h2;
							open.push_back({ f2, h2, g2, x2, y2 });
							closed_[x2][y2] = 1;
							
						}
						else
						{
							if (grid_[x2][y2] == 1)
							{
								expand_[x2][y2] = -1;
							}
						}
					}
				}
			}

		}
	}
	return expand_;
}
