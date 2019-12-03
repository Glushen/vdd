#include "gtest/gtest.h"
#include "vdd.h"
#include "util.h"

TEST(pointer, t1) {
    ASSERT_SUCCESS("int*x", "'x' is a pointer to type int");
}

TEST(pointer, t2) {
    ASSERT_SUCCESS("int**x", "'x' is a pointer to a pointer to type int");
}

TEST(pointer, t3) {
    ASSERT_SUCCESS("int(**(*x))", "'x' is a pointer to a pointer to a pointer to type int");
}
