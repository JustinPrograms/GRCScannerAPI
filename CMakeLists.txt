cmake_minimum_required(VERSION 3.24)
project(christianslogin)

set(CMAKE_CXX_STANDARD 17)

add_executable(christianslogin main.cpp json.h httplib.h)

# Link the christianslogin executable with the ws2_32 library
target_link_libraries(christianslogin PRIVATE ws2_32)
