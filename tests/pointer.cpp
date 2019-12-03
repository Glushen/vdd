#include "gtest/gtest.h"
#include "vdd.h"
#include "util.h"

TEST(pointer, t1) {
    ASSERT_SUCCESS("int*x", "'x' is a pointer to a value of type int");
}

TEST(pointer, t2) {
    ASSERT_SUCCESS("int**x", "'x' is a pointer to a pointer to a value of type int");
}

TEST(pointer, t3) {
    ASSERT_SUCCESS("int(**(*x))", "'x' is a pointer to a pointer to a pointer to a value of type int");
}

TEST(pointer, t4) {
    ASSERT_SUCCESS("long A::* p", "'p' is a pointer to member of type 'A' to a value of type long");
}

TEST(pointer, t5) {
    ASSERT_SUCCESS(
        "long A::* f()",
        "'f' is a function\n"
        "    without arguments\n"
        "    returning a pointer to member of type 'A' to a value of type long"
    );
}

TEST(pointer, t6) {
    ASSERT_SUCCESS(
        "long (A::* v)()",
        "'v' is a pointer to member of type 'A' to a function\n"
        "    without arguments\n"
        "    returning a value of type long"
    );
}
