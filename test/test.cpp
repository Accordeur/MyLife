//
// Created by Zelonge on 2021/4/13.
//

#include <gtest/gtest.h>
#include <numeric>
#include <vector>

TEST(MyLifeTest, Sum)
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    EXPECT_EQ(sum, 15);
}
