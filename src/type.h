#pragma once

#include <string>
#include <utility>

namespace vdd {
    const unsigned int SIGNED = 0;
    const unsigned int UNSIGNED = 1;
    const unsigned int CHAR = 2;
    const unsigned int SHORT = 4;
    const unsigned int INT = 8;
    const unsigned int LONG = 16;
    const unsigned int LONG_LONG = 32;
    const unsigned int FLOAT = 64;
    const unsigned int DOUBLE = 128;

    class Type {
    public:
        unsigned int numericTypeMask;
        std::string anotherTypeName;

        explicit Type(unsigned int numericTypeMask);
        explicit Type(std::string anotherTypeName);

        void print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames);
    };
}
