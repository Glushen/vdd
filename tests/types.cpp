#include "gtest/gtest.h"
#include "vdd.h"
#include "util.h"

TEST(types, i) {
    ASSERT_SUCCESS("int x", "'x' is a variable of type int");
}

TEST(types, ui1) {
    ASSERT_SUCCESS("unsigned int x", "'x' is a variable of type unsigned int");
}

TEST(types, ui2) {
    ASSERT_SUCCESS("int unsigned x", "'x' is a variable of type unsigned int");
}

TEST(types, uc) {
    ASSERT_SUCCESS("char unsigned x", "'x' is a variable of type unsigned char");
}

TEST(types, ss) {
    ASSERT_SUCCESS("signed short x", "'x' is a variable of type short");
}

TEST(types, l) {
    ASSERT_SUCCESS("long x", "'x' is a variable of type long");
}

TEST(types, f) {
    ASSERT_SUCCESS("float x", "'x' is a variable of type float");
}

TEST(types, lf) {
    ASSERT_FAIL("long float x");
}

TEST(types, d) {
    ASSERT_SUCCESS("double x", "'x' is a variable of type double");
}

TEST(types, ld1) {
    ASSERT_SUCCESS("long double x", "'x' is a variable of type long double");
}

TEST(types, ld2) {
    ASSERT_SUCCESS("double long x", "'x' is a variable of type long double");
}

TEST(types, sf) {
    ASSERT_FAIL("signed float x");
}

TEST(types, ud) {
    ASSERT_FAIL("unsigned double x");
}

TEST(types, ull) {
    ASSERT_SUCCESS("long int long unsigned x", "'x' is a variable of type unsigned long long");
}

TEST(types, ulll) {
    ASSERT_FAIL("long int long long unsigned x");
}

