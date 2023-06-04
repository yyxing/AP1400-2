cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)
set(GTEST "D:\\gtest\\")

find_package(OpenSSL REQUIRED)

include_directories(include/)
include_directories("${GTEST}/include")
link_directories("${GTEST}/lib")


add_executable(main
        src/main.cpp
        src/server.cpp
        src/client.cpp
        src/crypto.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        OpenSSL::SSL
        gtest
)