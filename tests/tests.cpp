#include "gtest/gtest.h"
#include "vdd.h"

TEST(tests, temp_test) {
    ASSERT_EQ(vdd::parseStatement("123"), "temp");
}
