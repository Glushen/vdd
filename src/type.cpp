#include <cassert>
#include <unordered_set>
#include <iostream>
#include "type.h"

vdd::Type::Type(unsigned int numericTypeMask):
    numericTypeMask(numericTypeMask),
    anotherTypeName() { }

vdd::Type::Type(std::string anotherTypeName):
    numericTypeMask(-1),
    anotherTypeName(std::move(anotherTypeName)) { }

void vdd::Type::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames) {
    if (!anotherTypeName.empty()) {
        if (templateTypenames.count(anotherTypeName)) {
            output << "template ";
        }
        output << "type '" << anotherTypeName << '\'';
        return;
    }

    output << "type ";

    if (numericTypeMask & UNSIGNED) {
        output << "unsigned ";
    }

    if (numericTypeMask & CHAR) {
        output << "char";
        return;
    }

    if (numericTypeMask & SHORT) {
        output << "short";
        return;
    }

    if (numericTypeMask & FLOAT) {
        output << "float";
        return;
    }

    if (numericTypeMask & DOUBLE) {
        if (numericTypeMask & LONG) {
            output << "long ";
        }
        output << "double";
        return;
    }

    if (numericTypeMask & LONG_LONG) {
        output << "long long";
        return;
    }

    if (numericTypeMask & LONG) {
        output << "long";
        return;
    }

    assert(numericTypeMask & INT);
    output << "int";
}
