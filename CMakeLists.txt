cmake_minimum_required(VERSION 3.13)

project(cpp_vdd_run)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_vdd_run main.cpp)

include_directories(src)
add_subdirectory(src)

target_link_libraries(cpp_vdd_run cpp_vdd_lib)

add_subdirectory(tests)
