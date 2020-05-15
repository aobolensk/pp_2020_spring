// Copyright 2020 Trenina Elizaveta

#include "gtest/gtest.h"
#include <algorithm>
#include <vector>
#include "./convex_hull_graham.h"
#include <stdio.h>
#include <iostream>



TEST(Graham_Alg, Test_point) {

	point p0(1.1, 0.0);
	point p1(0.0, 0.0);
	std::cout << "p1="<< p1.x << ", " << p1.y << std::endl;

}

TEST(Graham_Alg, Test_cmp) {

	point B(5.0, 10.0);
	point C(10.0, 2.0);
	bool res = cmp(B, C);
	std::cout << "res= " << res << std::endl;
}

TEST(Graham_Alg, Test_Getrand) {

	
	ASSERT_NO_THROW(GetRandSet(5));

}

TEST(Graham_Alg, Test_Getrand2) {


	ASSERT_NO_THROW(std::vector<point> Q = GetRandSet(5));

}
TEST(Graham_Alg, Test_Getrand3) {
	std::vector<point> Q = GetRandSet(5);
		ASSERT_EQ(Q.size(), 5);
	

}



TEST(Graham_Alg, Graham_Test) {

    std::vector<point> set{ {-1, 3}, {2, 5}, {4, 2},  {2, 0}, {-2, -1},
                               {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2} };
    std::vector<point> hull = Graham(set);
    std::vector<point> exp_hull{ {-2, -1}, {2, 0}, {4, 2}, {2, 5}, {-1, 3}, {-4, 1} };

    ASSERT_EQ(hull, exp_hull);
}




////#include <gtest/gtest.h>
//#include <gtest/gtest.h>
//
//#include <algorithm>
//#include <vector>
////#include "./convex_hull_graham.h"
//#include "../../../modules/task_1/trenina_e_convex_hull_graham/convex_hull_graham.h"


TEST(test_case, tetsname) {
	ASSERT_EQ(1, 1);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}