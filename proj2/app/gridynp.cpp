
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

void initialize_border(std::vector<std::vector<std::string> >& grid, std::vector<std::vector<int> >& calc, std::vector<std::vector<std::string> >& d_tracker, std::vector<std::vector<int> >& d_values, std::vector<std::vector<std::string> >& p_tracker, std::vector<std::vector<int> >& p_values)  {
	int size = grid.size();
	int start = 1;
	for(int i = 0; i < size; i++) {
		if(grid[0][i] == "P") {
			calc[0][i] = start;
			p_tracker[0][i] = "P";
			p_values[0][i] = start;
			if(i - 1 >= 0 and d_tracker[0][i-1] == "D") {
				d_tracker[0][i] = "D";
				d_values[0][i] = d_values[0][i-1];
			}
		} else if(grid[0][i] == "D") {
			calc[0][i] = start;
			d_tracker[0][i] = "D";
			d_values[0][i] = start;
			if(i - 1 >= 0 and p_tracker[0][i-1] == "P") {
				p_tracker[0][i] = "P";
				p_values[0][i] = p_values[0][i-1];
			}
		} else {
			//These are just all the numerical values
			int value = std::stoi(grid[0][i]);
			if(value > 0 and d_tracker[0][i-1] == "D") {
				//So in this case, we have a D in the chamber, and we want to use it
				calc[0][i] = start + (2 * value);
				d_values[0][i] = calc[0][i]; //We save it, but don't continue the D
				if(p_tracker[0][i-1] == "P") {
					p_values[0][i] = p_values[0][-1] + (2 * value);
					p_tracker[0][i] = "P";
				}
			} else if(value < 0 and p_tracker[0][i-1] == "P") {
				calc[0][i] = start;
				p_values[0][i] = start; //This will save the p value 
				if(d_tracker[0][i-1] == "D") {
					d_values[0][i] = d_values[0][i-1];
					d_tracker[0][i] = "D";
				}
			} else if(value >= 0 or value < 0) {
				//This is just normal arithmetic
				calc[0][i] = start + std::stoi(grid[0][i]);
				start += std::stoi(grid[0][i]);
			}
		}
		
	}
	start = 1;
	for(int i = 0; i < size; i++) {
		if(grid[i][0] == "P") {
			calc[0][i] = start;
			p_tracker[i][0] = "P";
			p_values[i][0] = start;
			if(i - 1 >= 0 and d_tracker[i-1][0] == "D") {
				d_tracker[i][0] = "D";
				d_values[i][0] = d_values[i-1][0];
			}
		} else if(grid[i][0] == "D") {
			calc[0][i] = start;
			d_tracker[i][0] = "D";
			d_values[i][0] = start;
			if(i - 1 >= 0 and p_tracker[i-1][0] == "P") {
				p_tracker[i][0] = "P";
				p_values[i][0] = p_values[i-1][0];
			}
		} else {
			//These are just all the numerical values
			int value = std::stoi(grid[i][0]);
			if(value > 0 and d_tracker[i-1][0] == "D") {
				//So in this case, we have a D in the chamber, and we want to use it
				calc[i][0] = start + (2 * value);
				d_values[i][0] = calc[i][0]; //We save it, but don't continue the D
				if(p_tracker[i-1][0] == "P") {
					p_values[i][0] = p_values[0][-1] + (2 * value);
					p_tracker[i][0] = "P";
				}
			} else if(value < 0 and p_tracker[i-1][0] == "P") {
				calc[i][0] = start;
				p_values[i][0] = start; //This will save the p value 
				if(d_tracker[i-1][0] == "D") {
					d_values[i][0] = d_values[0][i-1];
					d_tracker[i][0] = "D";
				}
			} else if(value >= 0 or value < 0) {
				//This is just normal arithmetic
				calc[i][0] = start + std::stoi(grid[i][0]);
				start += std::stoi(grid[i][0]);
			}
		}
	}
}

void new_queue(std::queue<std::pair<int, int> >& new_queue, std::queue<std::pair<int, int> >& old_queue, 
std::vector<std::vector<int> >& calc, std::vector<std::vector<std::string> >& grid, std::set<int>& path,
std::vector<std::vector<std::string> >& main_p, std::vector<std::vector<std::string> >& main_d) {
	//This will empty whatever path queue is currently be looking it
	//It will generate the next points in the queue
	//And it will add to the path
	while(old_queue.size() != 0) {
		std::pair<int, int> point = old_queue.front();
		int curr_point = calc[point.first][point.second];
		int op = std::stoi(grid[point.first][point.second]);
		op *= -1;
		if(point.first - 1 >= 0) {
			std::cout << op << " ";
			int prev_value = curr_point;
			if(std::stoi(grid[point.first][point.second]) > 0 and main_d[point.first - 1][point.second] == "D") {
				std::cout << " this is doubled " << " ";
				op *= 2;
				prev_value += op;
			} else if(std::stoi(grid[point.first][point.second]) > 0) {
				std::cout << " not doubled ";
				prev_value += op;
			}

			if(std::stoi(grid[point.first][point.second]) < 0 and main_d[point.first - 1][point.second] != "P") {
				prev_value += op;
			}

			std::cout << " " << prev_value << std::endl;

			
			if(prev_value == calc[point.first - 1][point.second]) {
				path.insert(prev_value);
				std::pair<int, int> new_point;
				new_point.first = point.first - 1;
				new_point.second = point.second;
				new_queue.push(new_point);
			}
		}
		op = std::stoi(grid[point.first][point.second]);
		op *= -1;
		if(point.second - 1 >= 0) {
			int prev_value = curr_point;
			if(std::stoi(grid[point.first][point.second]) > 0 and main_d[point.first][point.second-1] == "D") {
				op *= 2;
				prev_value += op;
			} else {
				prev_value += op;
			}

			if(std::stoi(grid[point.first][point.second]) < 0 and main_d[point.first][point.second-1] != "P") {
				prev_value += op;
			}
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

int path(std::vector<std::vector<std::string> >& grid, std::vector<std::vector<int> >& calc, 
std::set<int>& path_one, std::set<int>& path_two, std::queue<std::pair<int, int> >& q_one, 
std::queue<std::pair<int, int> >& q_two, std::vector<std::vector<std::string> >& main_d, 
std::vector<std::vector<std::string> >& main_p) {
	int size = grid.size();
	//This is to start it;
	path_one.insert(calc[size-2][size-1]);
	path_two.insert(calc[size-1][size-2]);
	int total = (2 * size) - 2;
	while(total) {
		std::queue<std::pair<int, int> > new_queue_one;
		new_queue(new_queue_one, q_one, calc, grid, path_one, main_d, main_p);
		q_one = new_queue_one;
		std::queue<std::pair<int, int> > new_queue_two;
		new_queue(new_queue_two, q_two, calc, grid, path_two, main_d, main_p);
		q_two = new_queue_two;
		total--;
	}
	return 0;
}

unsigned solve(std::vector<std::vector<std::string> > grid) {

	//Generate the graph for the calculations
	short size = grid.size();
	std::vector<std::vector<int> > calc (size, std::vector<int> (size));

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

	initialize_border(grid, calc, d_instance, d_track, p_instance, p_track);

	//Initialize the calculation graph

	//Define path lists
	std::set<int> path_one;
	std::set<int> path_two;
	std::queue<std::pair<int, int> > top_path;
	std::queue<std::pair<int, int> > left_path;
	std::vector<std::vector<std::string> > main_d_path (size, std::vector<std::string> (size));
	std::vector<std::vector<std::string> > main_p_path (size, std::vector<std::string> (size));
	main_d_path = d_instance; //Initially set it to the one found in the initializer
	main_p_path = p_instance; //Same here


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
				//First select along the main path;
				int next_value = std::max(top, left);

				calc[i][j] = next_value;

				if(d_instance[i][j-1] == "D" or d_instance[i-1][j] == "D") {
					//So check in the underlying map if D is in either of the previous nodes
					int under_top = d_track[i-1][j];
					int under_left = d_track[i][j-1];
					int next_under_d = std::max(under_top, under_left);
					d_instance[i][j] = "D";
					d_track[i][j] = next_under_d; //Set the next d
				}

				if(p_instance[i][j-1] != "P" and p_instance[i-1][j] != "P") {
					//THis is an empty instance
					p_instance[i][j] = "P";
					p_track[i][j] = next_value;
				} else {
					int under_top = p_track[i-1][j];
					int under_left = p_track[i][j-1];
					int next_under_p = std::max(next_value, under_top);
					next_under_p = std::max(under_left, next_under_p);
					p_instance[i][j] = "P";
					p_track[i][j] = next_under_p;
				}

				point = next_value;

				//You need to check if you have a P here, the value will replace it
			} else if(grid[i][j] == "D") {
				//This will pretty much be an mirror of the previous one
				int next_value = std::max(top, left);

				calc[i][j] = next_value;

				if(d_instance[i][j-1] == "P" or d_instance[i-1][j] == "P") {
					//So check in the underlying map if D is in either of the previous nodes
					int under_top = p_track[i-1][j];
					int under_left = p_track[i][j-1];
					int next_under_p = std::max(under_top, under_left);
					p_instance[i][j] = "P";
					p_track[i][j] = next_under_p; //Set the next d
				}

				if(d_instance[i][j-1] != "D" and d_instance[i-1][j] != "D") {
					//THis is an empty instance
					d_instance[i][j] = "D";
					d_track[i][j] = next_value;
				} else {
					int under_top = d_track[i-1][j];
					int under_left = d_track[i][j-1];
					int next_under_d = std::max(next_value, under_top);
					next_under_d = std::max(under_left, next_under_d);
					d_instance[i][j] = "D";
					d_track[i][j] = next_under_d;
				}

				point = next_value;
			} else if(grid_num > 0) {
				//Then we need to account for D
				if(main_d_path[i-1][j] == "D") {
					//Then we are looking at a node that needs to be doubled
					top += (2 * grid_num);
				} else {
					top += grid_num;
				}

				if(main_d_path[i][j-1] == "D") {
					left += (2 * grid_num);
				} else {
					left += grid_num;
				}

				//This is the point just doing the basic greedy path
				point = std::max(top, left);

				//Now we need to check the under graph;
				bool under_has_changed = false;
				int under_top = 0;
				if(d_instance[i-1][j] == "D") {
					under_has_changed = true;
					under_top = d_track[i-1][j] + (2 * grid_num);
				}

				int under_left = 0;
				if(d_instance[i][j-1] == "D") {
					under_has_changed = true;
					under_left = d_track[i][j-1] + (2 * grid_num);
				}

				if(under_has_changed) {
					int max_under = std::max(under_top, under_left);

					//So now we compare with the the max_under_for_d and the main_path d
					//I should make this a conditinal
					point = std::max(point, max_under);
				}

				//Now we need to apply the operations to the p path
				int under_top_p = 0;
				if(p_instance[i-1][j] == "P") {
					if(d_instance[i-1][j] == "D" or main_d_path[i-1][j] == "D") {
						//So this will see if we need to double the input 
						under_top_p = p_track[i-1][j] + (2 * grid_num);
					} else {
						under_top_p = p_track[i-1][j] + grid_num;
					}
					p_instance[i][j] = "P";
				}

				int under_left_p = 0;
				if(p_instance[i][j-1] == "P") {
					if(p_instance[i][j-1] == "D" or main_d_path[i][j-1] == "D") {
						//So this will see if we need to double the input 
						under_left_p = p_track[i][j-1] + (2 * grid_num);
					} else {
						under_left_p = p_track[i][j-1] + grid_num;
					}
					
					p_instance[i][j] = "P";
				}

				if(p_instance[i][j-1] == "P" or p_instance[i-1][j] == "P") {
					p_track[i][j] = std::max(under_top_p, under_left_p);
				}

				if(main_p_path[i-1][j] == "P" or main_p_path[i][j-1] == "P") {
					//Somewhere along the previous path, there was a P value that wasn't used in the main path.
					main_p_path[i][j] = "P";
				}
			} else {
				//Then we need to account for P
				if(main_p_path[i-1][j] != "P") {
					//Then we are looking at a node that needs to be doubled
					top += grid_num;
				}

				if(main_p_path[i][j-1] != "P") {
					left += grid_num;
				}

				point = std::max(top, left);

				//Now we need to check the under graph;
				bool under_has_changed = false;
				int under_top = 0;
				if(p_instance[i-1][j] == "P") {
					under_has_changed = true;
					under_top = p_track[i-1][j];
				}

				int under_left = 0;
				if(p_instance[i][j-1] == "P") {
					under_has_changed = true;
					under_left = p_track[i][j-1];
				}

				if(under_has_changed) {
					int max_under = std::max(under_top, under_left);

					//So now we compare with the the max_under_for_d and the main_path d
					//I should make this a conditinal
					point = std::max(point, max_under);
				}

				int under_top_d= 0;
				bool under_top_d_bool = false;
				if(d_instance[i-1][j] == "D") {
					//I guess if a p is applied then we need to account for it here
					if(p_instance[i-1][j] == "P" or main_p_path[i-1][j] == "P") {
						under_top_d = d_track[i-1][j];
					} else {
						under_top_d = d_track[i-1][j] + grid_num;
					}
					under_top_d_bool = true;
					d_instance[i][j] = "D";
				}


				int under_left_d= 0;
				bool under_left_d_bool = false;
				if(d_instance[i][j-1] == "D") {
					if(p_instance[i][j-1] == "P" or main_p_path[i][j-1] == "P") {
						under_left_d = d_track[i][j-1];
					} else {
						under_left_d = d_track[i][j-1] + grid_num;
					}
					under_left_d_bool = true;
					d_instance[i][j] = "D";
				}

				if(d_instance[i][j-1] == "D" or d_instance[i-1][j] == "D") {
					if(under_top_d_bool ==  true and under_left_d_bool == false) {
						d_track[i][j] = under_top_d;
					} 
					if(under_left_d_bool == true and under_top_d_bool == false) {
						d_track[i][j] = under_left_d;
					} 
					if(under_left_d_bool == true and under_top_d_bool == true) {
						d_track[i][j] = std::max(under_top_d, under_left_d);
					}
				}

				if(main_d_path[i-1][j] == "D" or main_d_path[i][j-1] == "D") {
					//Somewhere along the previous path, there was a P value that wasn't used in the main path.
					main_d_path[i][j] = "D";
				}
			}

			//Save the point here
			if(i == size - 1 and j == size - 1) {
				std::pair<int, int> point;
				point.first = i - 1;
				point.second = j;
				path_one.insert(top);
				top_path.push(point);
				point.first = i;
				point.second = j - 1;
				path_two.insert(left);
				left_path.push(point);
			} else {
				calc[i][j] = point;
			}
		}
	}

	display_graph(calc);

	path(grid, calc, path_one, path_two, top_path, left_path, main_d_path, main_p_path);
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

