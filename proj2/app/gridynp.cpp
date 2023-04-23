
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include "gridynp.hpp"

int path(std::vector<std::vector<std::string> >& grid, std::vector<std::vector<int> >& calc, std::vector<int>& path_one, std::vector<int>& path_two, std::queue<std::pair<int, int> >& q_one, std::queue<std::pair<int, int> >& q_two) {
	int size = grid.size();
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
	//This is to start it;
	path_one.push_back(calc[size-2][size-1]);
	path_two.push_back(calc[size-1][size-2]);
	int total = (2 * size) - 2;
	while(total != 0) {
		std::queue<std::pair<int, int> > new_path_one;
		while(q_one.size() != 0) {
			std::cout << "Is this even running" << std::endl;
			std::pair<int, int> point = q_one.front();
			int curr_point = calc[point.first][point.second];
			int op = std::stoi(grid[point.first][point.second]);
			op *= -1;
			if(point.first - 1 >= 0) {
				int next_value = curr_point + op;
				if(next_value == calc[point.first - 1][point.second]) {
					path_one.push_back(next_value);
					std::pair<int, int> new_point;
					new_point.first = point.first - 1;
					new_point.second = point.second;
					new_path_one.push(new_point);
				}
			}
			if(point.second - 1 >= 0) {
				int next_value = curr_point + op;
				if(next_value == calc[point.first][point.second-1]) {
					path_one.push_back(next_value);
					std::pair<int, int> new_point;
					new_point.first = point.first;
					new_point.second = point.second-1;
					new_path_one.push(new_point);
				}
			}
			q_one.pop();
		}
		q_one = new_path_one;
		std::queue<std::pair<int, int> > new_path_two;
		while(q_two.size() != 0) {
			std::pair<int, int> point = q_two.front();
			int curr_point = calc[point.first][point.second];
			int op = std::stoi(grid[point.first][point.second]);
			op *= -1;
			if(point.first - 1 >= 0) {
				int next_value = curr_point + op;
				if(next_value == calc[point.first - 1][point.second]) {
					path_two.push_back(next_value);
					std::pair<int, int> new_point;
					new_point.first = point.first - 1;
					new_point.second = point.second;
					new_path_two.push(new_point);
				}
			}
			if(point.second - 1 >= 0) {
				int next_value = curr_point + op;
				if(next_value == calc[point.first][point.second-1]) {
					path_two.push_back(next_value);
					std::pair<int, int> new_point;
					new_point.first = point.first;
					new_point.second = point.second-1;
					new_path_two.push(new_point);
				}
			}
			q_two.pop();
		}
		q_two = new_path_two;
		total--;
	}
	return 0;
}

unsigned solve(std::vector<std::vector<std::string> > grid) {

	//Generate the graph for the calculations
	short size = grid.size();
	std::vector<std::vector<int> > calc (size, std::vector<int> (size));

	//Initialize the calculation graph
	int start = 1;
	for(int i = 0; i < size; i++) {
		calc[0][i] = start + std::stoi(grid[0][i]);
		start += std::stoi(grid[0][i]);
	}
	start = 1;
	for(int i = 0; i < size; i++) {
		calc[i][0] = start + std::stoi(grid[i][0]);
		start += std::stoi(grid[i][0]);
	}

	//Define path lists
	std::vector<int> path_one;
	std::vector<int> path_two;
	std::queue<std::pair<int, int> > top_path;
	std::queue<std::pair<int, int> > left_path;


	//So calculate the body here
	for(int i = 1; i < size; i++) {
		for(int j = 1; j < size; j++) {
			int grid_num = std::stoi(grid[i][j]);
			//Get the previous points
			int top = calc[i-1][j];
			int left = calc[i][j-1];
			int point = 0;
			//------------
			if(grid[i][j] == "P") {
				continue;
			} else if(grid[i][j] == "D") {
				continue;
			} else if(grid_num == 0) {
				//Then we are working with zero and nothing happens
				continue;
			} else if(grid_num > 0) {
				//Then we need to account for D
				point = std::max(top + grid_num, left + grid_num);
			} else {
				std::cout << "Is it here" << std::endl;
				std::cout << top << std::endl;
				std::cout << left << std::endl;
				//Then we need to account for P
				point = std::max(top + grid_num, left + grid_num);
				std::cout << point << std::endl;
			}
			//Save the point here
			if(i == size - 1 and j == size - 1) {
				std::pair<int, int> point;
				point.first = i - 1;
				point.second = j;
				path_one.push_back(top + grid_num);
				top_path.push(point);
				point.first = i;
				point.second = j - 1;
				path_two.push_back(left + grid_num);
				left_path.push(point);
			} else {
				calc[i][j] = point;
			}
		}
	}

	path(grid, calc, path_one, path_two, top_path, left_path);
	int min_one = path_one[0];
	int min_two = path_two[0];
	for(auto i: path_one) {
		std::cout << i << " ";
		min_one = std::min(min_one, i);
	}
	std::cout << std::endl;
	for(auto i: path_two) {
		std::cout << i << " ";
		min_two = std::min(min_two, i);
	}
	std::cout << std::endl;
	int min_loss = std::max(min_one, min_two);
	if(min_loss >= 0) {
		std::cout << "Minimum hit points is 1" << std::endl;
	} else {
		std::cout << ((1 - (min_loss)) + 1) << std::endl;
	}
	return 0;
}

