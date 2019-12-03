#include "gtest/gtest.h"
#include "vdd.h"
#include "util.h"

TEST(ambiguous, t1) {
    ASSERT_FAIL("int f(int (x))", "syntax is ambiguous");
}