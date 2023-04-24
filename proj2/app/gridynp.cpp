
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "gridynp.hpp"

void display_graph(std::vector<std::vector<std::string> >& graph) {
	int size = graph.size();
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			std::cout << graph[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

void display_graph(std::vector<std::vector<int> >& graph) {
	int size = graph.size();
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			std::cout << graph[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

void initialize_border(std::vector<std::vector<std::string> >& grid, std::vector<std::vector<int> >& calc)  {
	int size = grid.size();
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
}

void new_queue(std::queue<std::pair<int, int> >& new_queue, std::queue<std::pair<int, int> >& old_queue, std::vector<std::vector<int> >& calc, std::vector<std::vector<std::string> >& grid, std::set<int>& path) {
	//This will empty whatever path queue is currently be looking it
	//It will generate the next points in the queue
	//And it will add to the path
	while(old_queue.size() != 0) {
		std::pair<int, int> point = old_queue.front();
		int curr_point = calc[point.first][point.second];
		int op = std::stoi(grid[point.first][point.second]);
		op *= -1;
		if(point.first - 1 >= 0) {
			int prev_value = curr_point + op;
			if(prev_value == calc[point.first - 1][point.second]) {
				path.insert(prev_value);
				std::pair<int, int> new_point;
				new_point.first = point.first - 1;
				new_point.second = point.second;
				new_queue.push(new_point);
			}
		}
		if(point.second - 1 >= 0) {
			int prev_value = curr_point + op;
			if(prev_value == calc[point.first][point.second - 1]) {
				path.insert(prev_value);
				std::pair<int, int> new_point;
				new_point.first = point.first;
				new_point.second = point.second -  1;
				new_queue.push(new_point);
			}
		}
		old_queue.pop();
	}
}

int path(std::vector<std::vector<std::string> >& grid, std::vector<std::vector<int> >& calc, std::set<int>& path_one, std::set<int>& path_two, std::queue<std::pair<int, int> >& q_one, std::queue<std::pair<int, int> >& q_two) {
	int size = grid.size();
	//This is to start it;
	path_one.insert(calc[size-2][size-1]);
	path_two.insert(calc[size-1][size-2]);
	int total = (2 * size) - 2;
	while(total) {
		std::queue<std::pair<int, int> > new_queue_one;
		new_queue(new_queue_one, q_one, calc, grid, path_one);
		q_one = new_queue_one;
		std::queue<std::pair<int, int> > new_queue_two;
		new_queue(new_queue_two, q_two, calc, grid, path_two);
		q_two = new_queue_two;
		total--;
	}
	return 0;
}

unsigned solve(std::vector<std::vector<std::string> > grid) {

	//Generate the graph for the calculations
	short size = grid.size();
	std::vector<std::vector<int> > calc (size, std::vector<int> (size));

	initialize_border(grid, calc);

	//Display the graph
	display_graph(calc);
	std::cout << "-----" << std::endl;

	//Tracking D
	//So in this vector will be be instances where d is
	std::vector<std::vector<std::string> > d_instance(size, std::vector<std::string> (size));

	//This vector will actually keep track of the numerical values on any unused D path.
	std::vector<std::vector<int> > d_track (size, std::vector<int> (size));

	//Tracking P
	//So in this vector will be instances were p is
	std::vector<std::vector<std::string> > p_instance(size, std::vector<std::string> (size));

	//This vector will actually keep track of the numerical values on any unused P path.
	std::vector<std::vector<int> > p_track (size, std::vector<int> (size));

	//Initialize the calculation graph

	//Define path lists
	std::set<int> path_one;
	std::set<int> path_two;
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
				//Then we need to account for P
				point = std::max(top + grid_num, left + grid_num);
			}

			//Save the point here
			if(i == size - 1 and j == size - 1) {
				std::pair<int, int> point;
				point.first = i - 1;
				point.second = j;
				path_one.insert(top + grid_num);
				top_path.push(point);
				point.first = i;
				point.second = j - 1;
				path_two.insert(left + grid_num);
				left_path.push(point);
			} else {
				calc[i][j] = point;
			}
		}
	}

	display_graph(calc);

	std::cout << "-----------" << std::endl;
	path(grid, calc, path_one, path_two, top_path, left_path);
	int min_one = 1000000000;
	int min_two = 1000000000;
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

