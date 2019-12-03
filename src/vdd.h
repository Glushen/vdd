#pragma once

#include <string>

namespace vdd {
    struct Result {
        bool accepted = false;
        std::string output;
    };
    Result parseStatement(const std::string&);
}
