#include "type.h"

vdd::Type::Type(unsigned int numericTypeMask):
    numericTypeMask(numericTypeMask),
    anotherTypeName() { }

vdd::Type::Type(std::string anotherTypeName):
    numericTypeMask(-1),
    anotherTypeName(std::move(anotherTypeName)) { }
