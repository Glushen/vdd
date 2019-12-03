#include <string>
#include <iostream>
#include "vdd.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    auto result = vdd::parseStatement(input);
    if (result.accepted) {
        std::cout << result.output << std::endl;
        return 0;
    } else {
        std::cerr << "Error: " << result.output << std::endl;
        return 1;
    }
}
