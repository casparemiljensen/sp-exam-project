cmake_minimum_required(VERSION 3.30)
project(sp_exam_project)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/include)
add_subdirectory(lib/src)
add_subdirectory(lib/examples)

add_executable(sp_exam_project bin/src/main.cpp
        lib/include/vessels.hpp)

target_link_libraries(sp_exam_project PRIVATE stochastic-simulation)