
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
		std::pair<int, int> point = old_queue.front(); //Get the node at the top of the queue
		int number_val = calc[point.first][point.second]; //This is the second number value;
		int operand = 0;
		if(point.first - 1 >= 0) {
			//This will essentially just check the row association
			int op = 0;
			bool non_number = false;
			if(grid[point.first - 1][point.second] != "D" and grid[point.first - 1][point.second] != "P") {
				//This is essentially just looking at the node and seeing if its a number or not;
				op = std::stoi(grid[point.first - 1][point.second]) * (-1);
				non_number = true;
			}

			//I want to check if the operator is equal to what is on the grid afterwards
			int attempt_val = number_val + op;
			if(attempt_val == calc[point.first-1][point.second]) {
				//This means we have a match, we don't need to look forward for anything
			}
		}
		if(point.second - 1 >= 0) {
			int op = 0;
			if(grid[point.first][point.second-1] != "D" and grid[point.first][point.second-1] != "P") {
				//This is essentially just looking at the node and seeing if its a number or not;
				op = std::stoi(grid[point.first][point.second-1]) * (-1);
			}
		}
		old_queue.pop();
	}

	/*while(old_queue.size() != 0) {
		std::pair<int, int> point = old_queue.front();
		int curr_point = calc[point.first][point.second];
		std::cout << point.first << " " << point.second << std::endl;
		std::cout << "THis is also a grid value " << grid[point.first][point.second] << std::endl;
		int op = 0;
		if(grid[point.first][point.second] != "D" and grid[point.first][point.second] != "P") {
			op = std::stoi(grid[point.first][point.second]);
		}
		op *= -1;
		std::cout << "Is this happending" << std::endl;
		
		if(point.first - 1 >= 0) {
			std::cout << "This is happening first" << std::endl;
			std::cout << "THis is also a grid value " << grid[point.first][point.second] << std::endl;
			int prev_value = curr_point;
			if(main_d[point.first - 1][point.second] == "D") {
				op *= 2;
				prev_value += op;
			} else if(std::stoi(grid[point.first][point.second]) > 0) {
				std::cout << "Why is this running" << std::endl;
				prev_value += op;
			}

			std::cout << point.first << " " << point.second << std::endl;
			if(std::stoi(grid[point.first][point.second]) < 0 and main_p[point.first - 1][point.second] != "P") {
				prev_value += op;
			}

			std::cout << "This is from the top " << prev_value << std::endl;
			
			if(prev_value == calc[point.first - 1][point.second]) {
				std::cout << "This has to be a match " << std::endl;
				path.insert(prev_value);
				std::pair<int, int> new_point;
				new_point.first = point.first - 1;
				new_point.second = point.second;
				new_queue.push(new_point);
			}
		}
		op = 0;
		if(grid[point.first][point.second] != "D" and grid[point.first][point.second] != "P") {
			op = std::stoi(grid[point.first][point.second]);
		}
		op *= -1;
		op *= -1;
		std::cout << "------" << std::endl;
		if(point.second - 1 >= 0) {
			int prev_value = curr_point;
			std::cout << "This is the previous operation " << prev_value << std::endl;
			std::cout << "This is the grid value " << grid[point.first][point.second] << std::endl;
			if(std::stoi(grid[point.first][point.second]) > 0 and main_d[point.first][point.second-1] == "D") {
				std::cout << "Why is this running" << std::endl;
				op *= 2;
				prev_value += op;
			} else if(std::stoi(grid[point.first][point.second]) > 0) {
				prev_value += op;
			}
			std::cout << grid[point.first][point.second] << std::endl;
			std::cout << point.first << " " << point.second << std::endl;
			std::cout << "This is the current point " << prev_value << std::endl;
			std::cout << "This is a test " << grid[point.first][point.second] << std::endl;
			std::cout << "This is the previous operation " << prev_value << std::endl;

			if(std::stoi(grid[point.first][point.second]) < 0 and main_p[point.first][point.second-1] != "P") {
				prev_value += op;
			}

			std::cout << "This is also a test " << prev_value << std::endl;

			if(prev_value == calc[point.first][point.second - 1]) {
				std::cout << "Is this a match" << std::endl;
				path.insert(prev_value);
				std::pair<int, int> new_point;
				new_point.first = point.first;
				new_point.second = point.second -  1;
				new_queue.push(new_point);
			}
		}
		std::cout << "------" << std::endl;
		old_queue.pop();
	}*/
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
		new_queue(new_queue_one, q_one, calc, grid, path_one, main_p, main_d);
		q_one = new_queue_one;
		std::queue<std::pair<int, int> > new_queue_two;
		new_queue(new_queue_two, q_two, calc, grid, path_two, main_p, main_d);
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
				//Perform the main calculation here
				//-------
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
				//THis is basically just the best path from the start
				point = std::max(top, left);

				//-------
		
				//Now we need to check the other graph for D
				bool under_top_has_changed = false;
				int under_top = 0;
				if(d_instance[i-1][j] == "D") {
					under_top_has_changed = true;
					under_top = d_track[i-1][j] + (2 * grid_num);
				}

				bool under_left_has_changed = false;
				int under_left = 0;
				if(d_instance[i][j-1] == "D") {
					under_left_has_changed = true;
					under_left = d_track[i][j-1] + (2 * grid_num);
				}

				if(d_instance[i][j-1] == "D" or d_instance[i-1][j] == "D") {
					int max_under = 0;
					//The reason I do this is because I don't want the D to be in the underlying graph to mistakenly replaced by a zero when it shouldn't be
					if(under_top_has_changed ==  true and under_left_has_changed == false) {
						max_under = under_top;
					} 
					if(under_left_has_changed == true and under_top_has_changed == false) {
						max_under = under_left;
					} 
					if(under_left_has_changed == true and under_top_has_changed == true) {
						max_under = std::max(under_top, under_left);
					}

					d_track[i][j] = max_under;

					//Save a new maximum here
					point = std::max(point, max_under);
				}

				//Now we need to apply the operations to the p path
				bool under_top_p_has_changed = false;
				int under_top_p = 0;
				if(p_instance[i-1][j] == "P") {
					if(d_instance[i-1][j] == "D" or main_d_path[i-1][j] == "D") {
						//So this will see if we need to double the input 
						under_top_p = p_track[i-1][j] + (2 * grid_num);
					} else {
						under_top_p = p_track[i-1][j] + grid_num;
					}
					under_top_p_has_changed = true;
					p_instance[i][j] = "P";
				}

				bool under_left_p_has_changed = false;
				int under_left_p = 0;
				if(p_instance[i][j-1] == "P") {
					if(p_instance[i][j-1] == "D" or main_d_path[i][j-1] == "D") {
						//So this will see if we need to double the input 
						under_left_p = p_track[i][j-1] + (2 * grid_num);
					} else {
						under_left_p = p_track[i][j-1] + grid_num;
					}
					under_left_p_has_changed = true;
					p_instance[i][j] = "P";
				}

				if(p_instance[i][j-1] == "P" or p_instance[i-1][j] == "P") {
					if(under_top_p_has_changed == true and under_left_p_has_changed == false) {
						p_track[i][j] = under_top_p;
					} else if(under_left_p_has_changed == true and under_top_p_has_changed == false) {
						p_track[i][j] = under_left_p;
					} else if(under_left_p_has_changed == true and under_top_p_has_changed == true) {
						p_track[i][j] = std::max(under_top_p, under_left_p);
					}
					
				}


				//This is see if the "P" power up needs to persist on the main path
				//If this one isn't chosen, then something from the p_layer underneath was successful
				if(point == top and main_p_path[i-1][j] == "P") {
					main_p_path[i][j] = "P";
				}

				if(point == left and main_p_path[i][j-1] == "P") {
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
				bool under_top_has_changed = false;
				int under_top = 0;
				if(p_instance[i-1][j] == "P") {
					under_top_has_changed = true;
					under_top = p_track[i-1][j];
				}

				bool under_left_has_changed = false;
				int under_left = 0;
				if(p_instance[i][j-1] == "P") {
					under_left_has_changed = true;
					under_left = p_track[i][j-1];
				}

				if(p_instance[i][j-1] == "P" or p_instance[i-1][j] == "P") {
					int max_under = 0;
					if(under_top_has_changed == true and under_left_has_changed == false) {
						max_under = under_top;
					} else if(under_top_has_changed == false and under_left_has_changed == true) {
						max_under = under_left;
					} else {
						max_under = std::max(under_top, under_left);
					}
					//int max_under = std::max(under_top, under_left);

					p_track[i][j] = max_under;

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

				//This is see if the "D" power up needs to persist on the main path
				if(point == top and main_d_path[i-1][j] == "D") {
					main_d_path[i][j] = "D";
				}

				if(point == left and main_d_path[i][j-1] == "D") {
					main_d_path[i][j] = "D";
				}


			}

			//Save the point here
			if(i == size - 1 and j == size - 1) {
				//This is the last node
				std::pair<int, int> point;
				//Offset up one row
				point.first = i - 1;
				point.second = j;
				path_one.insert(top); //Save the value of the ending for one path here
				top_path.push(point);

				//Offset down one row
				point.first = i;
				point.second = j - 1;
				path_two.insert(left); //Save the value of hte ending for one path here
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
	if(min_loss > 0) {
		std::cout << "Minimum hit points is 1" << std::endl;
	} else {
		std::cout << ((1 - (min_loss)) + 1) << std::endl;
	}
	
	return 0;
}

