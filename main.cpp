#include <string>
#include <iostream>
#include "vdd.h"

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::cout << vdd::parseStatement(input);
}
