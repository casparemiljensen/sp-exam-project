cmake_minimum_required(VERSION 3.30)
project(sp_exam_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include("cmake/sanitizers.cmake")

enable_testing()

add_subdirectory(lib/src)

add_subdirectory(bin/src)

add_subdirectory(test)

add_subdirectory(benchmark)