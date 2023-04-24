
#ifndef __GRID_DYNAMIC_PROGRAMMING_HPP
#define __GRID_DYNAMIC_PROGRAMMING_HPP
#include <queue>
unsigned solve(std::vector<std::vector<std::string> > grid);
int path(std::vector<std::vector<int> >& grid, std::vector<int>& path_one, std::vector<int>& path_two, std::queue<std::pair<int, int> >& q_one, std::queue<std::pair<int, int> >& q_two);
void new_queue(std::queue<std::pair<int, int> >& new_queue, std::queue<std::pair<int, int> >& old_queue, std::vector<std::vector<int> >& calc, std::vector<std::vector<std::string> >& grid, std::vector<int>& path);
void initialize_border();
void display_graph(std::vector<std::vector<std::string> >& graph);
void display_graph(std::vector<std::vector<int> >& graph);
#endif
