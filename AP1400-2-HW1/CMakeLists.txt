cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 17)

set(GTEST "D:\\gtest\\")

include_directories(include/)
include_directories("${GTEST}/include")
link_directories("${GTEST}/lib")

add_executable(main
        src/main.cpp
        src/hw1.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        gtest
)

