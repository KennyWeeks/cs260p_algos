
#include <string>
#include <iostream>
#include <vector>
#include "gridynp.hpp"



unsigned solve(std::vector<std::vector<std::string> > grid) 
{
	unsigned size = grid.size();
	std::cout << size << std::endl;
	std::vector<std::vector<int> > pass (size, std::vector<int> (size));
	std::vector<std::vector<std::string> > p_power_up (size, std::vector<std::string> (size));
	std::vector<std::vector<std::string> > d_power_up (size, std::vector<std::string> (size));
	std::vector<std::vector<std::string> > d_keep_track(size, std::vector<std::string> (size));
	int start = 1;
	//Fill out top and left side
	for(int i = 0; i < size; i++) {
		if(grid[0][i] == "P") {
			p_power_up[0][i] = start;
			d_power_up[0][i] = d_power_up[0][i-1];
		} else if(grid[0][i] == "D") {
			d_power_up[0][i] = start;
			p_power_up[0][i] = p_power_up[0][i-1];
		} else {
			if(i > 0 and std::stoi(grid[0][i]) < 0 and p_power_up[0][i-1] != "x" and p_power_up[0][i] != "x") {
				pass[0][i] = start;
				p_power_up[0][i] = start;
				if(i + 1 < size) {
					p_power_up[0][i + 1] = "x";
					p_power_up[1][i] = "x";
				}
				d_power_up[0][i] = d_power_up[0][i-1];
			} else if(i > 0 and std::stoi(grid[0][i]) > 0 and d_power_up[0][i-1] != "x" and d_power_up[0][i] != "x") {
				pass[0][i] = start + (2 * std::stoi(grid[0][i]));
				start += (2 * std::stoi(grid[0][i]));
				d_power_up[0][i] = pass[0][i];
				if(i + 1 < size) {
					d_power_up[0][i + 1] = "x";
					d_power_up[1][i] = "x";
				}
				p_power_up[0][i] = p_power_up[0][i-1];
			} else {
				pass[0][i] = start + std::stoi(grid[0][i]);
				start += std::stoi(grid[0][i]);
				if(i == 0) {
					p_power_up[0][i] = "x";
					d_power_up[0][i] = "x";
				} else {
					p_power_up[0][i] = p_power_up[0][i-1];
					d_power_up[0][i] = d_power_up[0][i-1];
				}
			}
		}
		
	}
	start = 1;
	for(int i = 0; i < size; i++) {
		if(grid[i][0] == "D") {
			d_keep_track[i][0] = "D";
			d_power_up[i][0] = std::to_string(start);
		} else if(std::stoi(grid[i][0]) > 0 and d_keep_track[i-1][0] == "D") {
			pass[i][0] = start + (2 * std::stoi(grid[i][0]));
			start += (2 * std::stoi(grid[i][0]));
			d_power_up[i][0] = std::to_string(pass[i][0]);
		} else {
			pass[i][0] = start + std::stoi(grid[i][0]);
			start += std::stoi(grid[i][0]);
			if (i > 0 and d_keep_track[i-1][0] == "D") {
				d_keep_track[i][0] = "D";
				int sum = std::stoi(d_power_up[i-1][0]) + std::stoi(grid[i][0]);
				d_power_up[i][0] = std::to_string(sum);
			}
			
		}
	}
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(i == 0 or j == 0) {
				std::cout << pass[i][j] << " ";
			} else {
				std::cout << " __ "; 
			}
		}
		std::cout << std::endl;
	}
	std::cout << "------------" << std::endl;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(d_power_up[i][j] != "") {
				std::cout << d_power_up[i][j] << " ";
			} else {
				std::cout << " __ "; 
			}
		}
		std::cout << std::endl;
	}
	std::cout << "------------" << std::endl;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(d_keep_track[i][j] != "") {
				std::cout << d_keep_track[i][j] << " ";
			} else {
				std::cout << " __ "; 
			}
		}
		std::cout << std::endl;
	}
	/*for(int i =  1; i < size; i++) {
		for(int j = 1; j < size; j++) {
			int node = std::stoi(grid[i][j]);
			int left = pass[i][j-1] + node;
			int top = pass[i-1][j] + node;
			pass[i][j] = std::max(left, top);
			//unsigned left = pass[i][j-1] + std::stoi(grid[i][j]);
			//unsigned top = pass[i - 1][j] + std::stoi(grid[i][j]);
			//pass[i][j] = std::max(left, top);
		}
	}

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			std::cout << pass[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	return 1;
}

