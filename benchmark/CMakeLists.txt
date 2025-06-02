set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.30)

# find_package(benchmark REQUIRED)
add_executable(benchmarks benchmarks.cpp)
target_link_libraries(benchmarks PRIVATE
        benchmark::benchmark
        stochastic-simulation
)