#include "gtest/gtest.h"
#include "vdd.h"
#include "util.h"

TEST(tmplate, t1) {
    ASSERT_SUCCESS("template<typename T> T *x", "'x' is a pointer to template type 'T'");
}
