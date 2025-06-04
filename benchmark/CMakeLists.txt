include("../cmake/benchmark.cmake")

add_executable(benchmarks benchmarks.cpp
        ../lib/include/debug_print.hpp)
target_link_libraries(benchmarks PRIVATE
        benchmark::benchmark
        stochastic-simulation
)