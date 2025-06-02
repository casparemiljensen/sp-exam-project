# Downloads and compiles Google Benchmark
include(FetchContent)
set(FETCHCONTENT_QUIET ON)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Enable testing of the benchmark library.")
set(BENCHMARK_ENABLE_EXCEPTIONS ON CACHE BOOL "Enable the use of exceptions in the benchmark library.")
set(BENCHMARK_ENABLE_LTO OFF CACHE BOOL "Enable link time optimisation of the benchmark library.")
set(BENCHMARK_USE_LIBCXX OFF CACHE BOOL "Build and test using libc++ as the standard library.")
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "Build Release candidates with -Werror.")
set(BENCHMARK_FORCE_WERROR OFF CACHE BOOL "Build Release candidates with -Werror regardless of compiler issues.")
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)")
set(BENCHMARK_ENABLE_DOXYGEN OFF CACHE BOOL "Build documentation with Doxygen.")
set(BENCHMARK_INSTALL_DOCS OFF CACHE BOOL "Enable installation of documentation.")
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "Allow the downloading and in-tree building of unmet dependencies")
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Enable building the unit tests which depend on gtest")
set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "Use bundled GoogleTest. If disabled, the find_package(GTest) will be used.")
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3    # or "main" for latest
        GIT_SHALLOW TRUE  # download specific revision only (git clone --depth 1)
        GIT_PROGRESS TRUE # show download progress in Ninja
        USES_TERMINAL_DOWNLOAD TRUE)
FetchContent_MakeAvailable(googlebenchmark)

message(STATUS "!!! Benchmark comparison requires python3 and `pip install scipy` !!!")
set(benchmark_cmp python3 ${googlebenchmark_SOURCE_DIR}/tools/compare.py)
