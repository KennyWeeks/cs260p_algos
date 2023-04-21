#include <vector>
#include <gtest/gtest.h>
#include "gridynp.hpp"

// NOTE:  THESE MIGHT NOT BE COMPLETE TEST CASES
// IT IS POSSIBLE TO PASS SOME OR ALL OF THESE AND NOT
//  PASS THE ONES USED IN GRADING.
// THEY ARE TO GET YOU STARTED.

namespace{

	TEST(SampleTests, Sample1)
	{

			/* 
			 Note the optimal path:  heal 2 at top-left, move down and take 2 damage, move down again and heal 15.
			 		Then move right twice, taking 14 total damage.  If you started at 1 or more, you got this far, so 1 is the min HP we could have started with. 
			 */
		std::vector< std::vector< std::string> > grid = {
			{"2", "-1", "-13"}, 
			{"-2", "-30", "20"},
			{"15", "-13", "-1"}
		};

		EXPECT_EQ( solve(grid), 1 );
	}


	TEST(SampleTests, Sample2)
	{
		std::vector< std::vector< std::string> > grid = {
			{"3", "P", "D", "10"},
			{"-5", "-6", "-2", "-100"},
			{"1", "-4", "-5", "-24"},
			{"-3", "4", "6", "8"}
		};

		EXPECT_EQ( solve(grid) , 2 );
	}

	TEST(SampleTests, Sample3)
	{
		std::vector< std::vector< std::string> > grid = {
			{"5", "-6", "7", "-8", "9"},
			{"-6", "7", "-8", "9", "-10"},
			{"7", "-8", "9", "-10", "11"},
			{"-8", "9", "-10", "11", "-12"},
			{"9", "-10", "11", "-12", "13"}
		};

		EXPECT_EQ( solve(grid) , 5 );
	}


	TEST(SampleTests, Sample4)
	{
		std::vector< std::vector< std::string> > grid = {
			{"-1", "-1", "-1", "-1", "-1"},
			{"D", "1", "2", "3", "4"},
			{"-1", "-2", "-3", "1", "2"},
			{"5", "10", "-1", "1", "2"},
			{"10", "5", "50", "-1", "-300"}
		};

		EXPECT_EQ( solve(grid) , 210 );
	}


}
