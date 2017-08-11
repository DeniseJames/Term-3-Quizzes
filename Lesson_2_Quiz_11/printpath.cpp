#include "printpath.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;



printpath::printpath() : grid_({
	{ 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 } })
	, goal_({ (grid_.size() - 1) , (grid_[0].size() - 1) })
	, init_({ 0,0 })
	, cost_(1)
	, delta_({ { -1, 0 },  //go up
	{ 0,-1 },    //go left
	{ 1, 0 },    //go down
	{ 0, 1 } })  //go right 
{}

printpath::~printpath() {}

std::vector<std::vector<char>> printpath::Search() {
	char delta_name[] = {'^', '<','v', '>'};

	for (unsigned int i = 0; i < grid_.size(); i++) {
		vector<unsigned int> temp;
		for (unsigned int j = 0; j < grid_[0].size(); j++) {
			temp.push_back(0);
		}

		closed_.push_back(temp);
	}
	// Set the closed corresponding starting position
	closed_[init_[0]][init_[1]] = 1;
	// now define the printpath vector
	for (unsigned int i = 0; i < grid_.size(); i++) {
		vector<int> temp;
		for (unsigned int j = 0; j < grid_[0].size(); j++) {
			temp.push_back(-1);
		}
		expand_.push_back(temp);
	}
	// now define the action vector
	for (unsigned int i = 0; i < grid_.size(); i++) {
		vector<int> temp;
		for (unsigned int j = 0; j < grid_[0].size(); j++) {
			temp.push_back(-1);
		}
		action_.push_back(temp);
	}
	// Initialize x, y to starting grid position	
	int x = init_[0];
	int y = init_[1];
	int g = 0;
	int e = 0;

	// Declare and define an open 2-D matrix called open
	// one row, three elements in the row initialized to 0
	vector<vector<int>> open(1, vector<int>(3, 0));

	open = { { g, x, y } };
	expand_[x][y] = e;
	bool found = false; // set when search is complete
	bool resign = false; // set if we cannot printpath

	while (found == false && resign == false) {
		if (open.size() == 0) {
			resign = true;
		}
		else {
			sort(open.begin(), open.end());
			reverse(open.begin(), open.end());
			std::vector<int> next = open.back();
			open.pop_back();
			int g = next[0];
			int x = next[1];
			int y = next[2];

			if (x == goal_[0] && y == goal_[1]) {
				found = true;
			}
			else {
				for (unsigned int i = 0; i < delta_.size(); i++) {
					int x2 = x + delta_[i][0];
					int y2 = y + delta_[i][1];
					if (x2 >= 0 && x2 < grid_.size() && y2 >= 0 && y2 < grid_[0].size()) {
						if (closed_[x2][y2] == 0 && grid_[x2][y2] == 0) {
							e = e + cost_;
							int g2 = g + cost_;
							open.push_back({ g2, x2, y2 });
							closed_[x2][y2] = 1;
							expand_[x2][y2] = e;
							// action is the successor grid cell
							action_[x2][y2] = i;

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
	for (unsigned int i = 0; i < grid_.size(); i++) {
		vector<char> temp;
		for (unsigned int j = 0; j < grid_[0].size(); j++) {
			temp.push_back(' ');
		}
		policy_.push_back(temp);
	}

	x = goal_[0];
	y = goal_[1];
	// start at the goal finish at start
	while (x != init_[0] || y != init_[1])
	{
		int x2 = x - delta_[action_[x][y]][0];
		int y2 = y - delta_[action_[x][y]][1];
		policy_[x][y] = delta_name[action_[x][y]];
		x = x2;
		y = y2;

	}
	policy_[0][0] = 'S';
	policy_[goal_[0]][goal_[1]] = '*';
	return policy_;
}
