include("../cmake/benchmark.cmake")

add_executable(benchmarks benchmarks.cpp)
target_link_libraries(benchmarks PRIVATE
        benchmark::benchmark
        stochastic-simulation
)