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
)
target_link_libraries(main
        gtest
)

configure_file(${CMAKE_SOURCE_DIR}/resources/flights.txt ${CMAKE_CURRENT_BINARY_DIR}/flights.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/lung_cancer.csv ${CMAKE_CURRENT_BINARY_DIR}/lung_cancer.csv COPYONLY)