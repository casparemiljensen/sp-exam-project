cmake_minimum_required(VERSION 3.30)
project(sp_exam_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing() # Keep this if you have your own unit tests (like in 'test')

add_subdirectory(lib/src)

add_subdirectory(bin/src)

add_subdirectory(test)


# --- Configure Google Benchmark Submodule ---
# These variables MUST be set BEFORE add_subdirectory(extern/benchmark)
# The goal is to completely disable Google Test dependency for the benchmark submodule.
# We are prioritizing turning off the testing infrastructure.

## Forcefully set these to OFF to override any previous cached values.
#set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable building Google Benchmark's own tests" FORCE)
#set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable building Google Benchmark's testing framework" FORCE)
## Explicitly set DOWNLOAD_DEPENDENCIES to OFF, as we are not enabling tests that would need it.
#set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE BOOL "Ensure no download attempt for Google Benchmark's dependencies" FORCE)
#
## Now, add the Google Benchmark submodule itself
#add_subdirectory(extern/benchmark)


# This add_subdirectory will now find benchmark::benchmark from the submodule.
add_subdirectory(benchmark)