project(cpp_vdd_lib)

#find_package(BISON)
#find_package(FLEX)
#
#bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
#flex_target(lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
#add_flex_bison_dependency(lexer parser)

add_library(
    cpp_vdd_lib STATIC
    temp.h
    temp.cpp
    #    ${FLEX_lexer_OUTPUTS}
    #    ${BISON_parser_OUTPUTS}
)
