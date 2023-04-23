#include <vector>
#include <string>
#include <iostream>
#include "gridynp.hpp"

int main()
{
    std::vector< std::vector< std::string> > grid;

    std::vector<std::string> line;
    /*{"-1", "-1", "-1", "-1", "-1"},
		{"D", "1", "2", "3", "4"},
		{"-1", "-2", "-3", "1", "2"},
		{"5", "10", "-1", "1", "2"},
		{"10", "5", "50", "-1", "-300"}*/
    /*line.push_back("-1");
    line.push_back("-1");
    line.push_back("-1");
    line.push_back("-1");
    line.push_back("-1");
    grid.push_back(line);
    line.clear();
    line.push_back("D");
    line.push_back("1");
    line.push_back("2");
    line.push_back("3");
    line.push_back("4");
    grid.push_back(line);
    line.clear();
    line.push_back("-1");
    line.push_back("-2");
    line.push_back("-3");
    line.push_back("1");
    line.push_back("2");
    grid.push_back(line);
    line.clear();
    line.push_back("5");
    line.push_back("10");
    line.push_back("-1");
    line.push_back("1");
    line.push_back("2");
    grid.push_back(line);
    line.clear();
    line.push_back("10");
    line.push_back("5");
    line.push_back("50");
    line.push_back("-1");
    line.push_back("-300");
    grid.push_back(line);
    line.clear();
    solve(grid);*/
    line.push_back("2");
    line.push_back("-1");
    line.push_back("-13");
    grid.push_back(line);
    line.clear();
    line.push_back("-2");
    line.push_back("-30");
    line.push_back("20");
    grid.push_back(line);
    line.clear();
    line.push_back("15");
    line.push_back("-13");
    line.push_back("-1");
    grid.push_back(line);
    solve(grid);
    /*grid.push_back({"-2", "-30", "20"});
    grid.push_back({"15", "-13", "-1"});*/
    return 0;
}

