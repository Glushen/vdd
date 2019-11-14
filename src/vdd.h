#pragma once

#include <string>
#include <variant>

namespace vdd {
    std::variant<std::string, std::string> parseStatement(const std::string&);
}
