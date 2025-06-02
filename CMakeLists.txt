cmake_minimum_required(VERSION 3.30)
project(sp_exam_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

# Tilføj biblioteket
add_subdirectory(lib/src)

# Tilføj executable
add_subdirectory(bin/src)

# includere unit test
add_subdirectory(test)




