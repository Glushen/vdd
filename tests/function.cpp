#include "gtest/gtest.h"
#include "vdd.h"
#include "util.h"

TEST(function, t1) {
    ASSERT_SUCCESS(
        "int f()",
        "'f' is a function\n"
        "    without arguments\n"
        "    returning a value of type int"
    );
}

TEST(function, t2) {
    ASSERT_SUCCESS(
        "int* g(x)",
        "'g' is a function\n"
        "    with argument\n"
        "        a value of type 'x'\n"
        "    returning a pointer to a value of type int"
    );
}

TEST(function, t3) {
    ASSERT_SUCCESS(
        "int (g(X x))",
        "'g' is a function\n"
        "    with argument\n"
        "        'x' is a value of type 'X'\n"
        "    returning a value of type int"
    );
}

TEST(function, t4) {
    ASSERT_SUCCESS(
        "int g(X x, Y y, z)",
        "'g' is a function\n"
        "    with arguments\n"
        "        'x' is a value of type 'X'\n"
        "        'y' is a value of type 'Y'\n"
        "        a value of type 'z'\n"
        "    returning a value of type int"
    );
}

TEST(function, t5) {
    ASSERT_SUCCESS(
        "int (*f(a,b))(c,d)",
        "'f' is a function\n"
        "    with arguments\n"
        "        a value of type 'a'\n"
        "        a value of type 'b'\n"
        "    returning a pointer to a function\n"
        "        with arguments\n"
        "            a value of type 'c'\n"
        "            a value of type 'd'\n"
        "        returning a value of type int"
    );
}
