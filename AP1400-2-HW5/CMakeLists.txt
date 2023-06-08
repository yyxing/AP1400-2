cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)
set(GTEST "D:\\gtest\\")

include_directories(include/)
include_directories("${GTEST}/include")
link_directories("${GTEST}/lib")

add_executable(main
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)
target_link_libraries(main
        gtest
)