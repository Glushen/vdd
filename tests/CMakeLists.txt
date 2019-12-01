project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
    Google_Tests_run
    mixed.cpp
    types.cpp
    pointer.cpp
    template.cpp
    util.h util.cpp
)

target_link_libraries(Google_Tests_run cpp_vdd_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)