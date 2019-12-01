#pragma once
#include "gtest/gtest.h"
#include "vdd.h"

void ASSERT_SUCCESS(const std::string& input, const std::string& output);

void ASSERT_FAIL(const std::string& input);
