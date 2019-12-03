#include "util.h"

void ASSERT_SUCCESS(const std::string& input, const std::string& output) {
    auto result = vdd::parseStatement(input);
    ASSERT_TRUE(result.accepted);
    ASSERT_EQ(result.output, output);
}

void ASSERT_FAIL(const std::string& input, const std::string& output) {
    auto result = vdd::parseStatement(input);
    ASSERT_FALSE(result.accepted);
    ASSERT_EQ(result.output, output);
}
