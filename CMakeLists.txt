cmake_minimum_required(VERSION 3.14)
project(cpp_vdd)

set(CMAKE_CXX_STANDARD 17)

#find_package(BISON)
#find_package(FLEX)
#
#bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
#flex_target(lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
#add_flex_bison_dependency(lexer parser)

add_executable(
    cpp_vdd
    main.cpp
#    ${FLEX_lexer_OUTPUTS}
#    ${BISON_parser_OUTPUTS}
)
