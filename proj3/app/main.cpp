#include <iostream>
#include <vector>
#include "tspdynp.hpp"


int main()
{
    std::vector< std::vector< long > > distances = 
		{
			{0, 2, 9, 0}, 
				{1, 0, 6, 4}, 
				{0, 7, 0, 8}, 
				{6, 3, 0, 0}
		};
    std::vector<unsigned> journey = tsp_dynamic_program(distances, 4);
    return 0;
}
