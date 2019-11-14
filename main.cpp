#include <string>
#include <iostream>
#include <variant>
#include "vdd.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    auto result = vdd::parseStatement(input);
    if (result.index() == 0) {
        std::cout << std::get<0>(result);
    } else {
        std::cout << "Error: " << std::get<1>(result);
    }
}
