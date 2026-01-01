cmake_minimum_required(VERSION 3.5)

project(Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(messageparser.h)
add_executable(Parser main.cpp messageparser.cpp)

install(TARGETS Parser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
