#include "util.h"

void ASSERT_SUCCESS(const std::string& input, const std::string& output) {
    auto result = vdd::parseStatement(input);
    ASSERT_EQ(result.index(), 0);
    ASSERT_EQ(std::get<0>(result), output);
}

void ASSERT_FAIL(const std::string& input) {
    auto result = vdd::parseStatement(input);
    ASSERT_EQ(result.index(), 1);
}
