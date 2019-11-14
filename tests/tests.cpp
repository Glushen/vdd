#include "gtest/gtest.h"
#include "vdd.h"

TEST(tests, temp_test) {
    auto result = vdd::parseStatement("123");
    ASSERT_EQ(result.index(), 0);
    ASSERT_EQ(std::get<0>(result), "temp");
}
