#include <gtest/gtest.h>
#include <othello/core/hello.hpp>

TEST(HelloTest, BasicAssertion)
{
    EXPECT_EQ(1, ret_1());
}