cmake_minimum_required(VERSION 3.30)
project(sp_exam_project)

set(CMAKE_CXX_STANDARD 23)

#include_directories(include)
add_subdirectory(include)
add_subdirectory(source)

add_executable(sp_exam_project source/main.cpp
        include/vessels.hpp)

target_link_libraries(sp_exam_project PRIVATE stochastic-simulation)