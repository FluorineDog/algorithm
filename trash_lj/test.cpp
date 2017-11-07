#include "trash.h"
#include <gtest/gtest.h>
TEST(trash, case1){
	vector<tuple<size_t, double, size_t>> data {
		{1, 1, 3},
		{1, 2, 3},
		{1, 3, 3},
		{1, 4, 3},
		{1, 5, 3},
		{1, 6, 3},
	};
	EXPECT_EQ(6, multipack(data, 1)); 
	EXPECT_EQ(12, multipack(data, 2)); 
	EXPECT_EQ(18, multipack(data, 3)); 
	EXPECT_EQ(18 + 5, multipack(data, 4)); 
	EXPECT_EQ(18 + 10, multipack(data, 5)); 
	EXPECT_EQ(18 + 15, multipack(data, 6)); 
	EXPECT_EQ(18 + 15 + 4, multipack(data, 7)); 
	EXPECT_EQ(18 + 15 + 8, multipack(data, 8)); 
	EXPECT_EQ(18 + 15 + 12, multipack(data, 9)); 
	EXPECT_EQ(18 + 15 + 12 + 3, multipack(data, 10)); 
	EXPECT_EQ(18 + 15 + 12 + 6, multipack(data, 11)); 
	EXPECT_EQ(18 + 15 + 12 + 9, multipack(data, 12)); 
}