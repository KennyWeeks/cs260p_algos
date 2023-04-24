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
    line.push_back("-1");
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
    solve(grid);
    /*line.push_back("2");
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
    solve(grid);*/
    /*
    {"5", "-6", "7", "-8", "9"},
	{"-6", "7", "-8", "9", "-10"},
	{"7", "-8", "9", "-10", "11"},
	{"-8", "9", "-10", "11", "-12"},
	{"9", "-10", "11", "-12", "13"}
    */
   /*line.push_back("5");
   line.push_back("-6");
   line.push_back("7");
   line.push_back("-8");
   line.push_back("9");
   grid.push_back(line);
   line.clear();
   line.push_back("-6");
   line.push_back("7");
   line.push_back("-8");
   line.push_back("9");
   line.push_back("-10");
   grid.push_back(line);
   line.clear();
   line.push_back("7");
   line.push_back("-8");
   line.push_back("9");
   line.push_back("-10");
   line.push_back("11");
   grid.push_back(line);
   line.clear();
   line.push_back("-8");
   line.push_back("9");
   line.push_back("-10");
   line.push_back("11");
   line.push_back("-12");
   grid.push_back(line);
   line.clear();
   line.push_back("9");
   line.push_back("-10");
   line.push_back("11");
   line.push_back("-12");
   line.push_back("13");
   grid.push_back(line);
   line.clear();
   solve(grid);*/
    /*grid.push_back({"-2", "-30", "20"});
    grid.push_back({"15", "-13", "-1"});*/
    /*{"3", "P", "D", "10"},
			{"-5", "-6", "-2", "-100"},
			{"1", "-4", "-5", "-24"},
			{"-3", "4", "6", "8"}*/
    /*line.push_back("3");
    line.push_back("P");
    line.push_back("D");
    line.push_back("10");
    grid.push_back(line);
    line.clear();
    line.push_back("-5");
    line.push_back("-6");
    line.push_back("-2");
    line.push_back("-100");
    grid.push_back(line);
    line.clear();
    line.push_back("1");
    line.push_back("-4");
    line.push_back("-5");
    line.push_back("-24");
    grid.push_back(line);
    line.clear();
    line.push_back("-3");
    line.push_back("4");
    line.push_back("6");
    line.push_back("8");
    grid.push_back(line);
    solve(grid);*/
    return 0;
}

