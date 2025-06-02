

include(FetchContent)
set(FETCHCONTENT_QUIET ON)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

#set(DOCTEST_WITH_TESTS OFF CACHE BOOL "Build tests/examples")
set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "Build a static lib for doctest::doctest_with_main")
set(DOCTEST_NO_INSTALL OFF CACHE BOOL "Skip the installation process")
set(DOCTEST_USE_STD_HEADERS OFF CACHE BOOL "Use std headers")

FetchContent_Declare(doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11   # "main" for latest
        GIT_SHALLOW TRUE  # download specific revision only (git clone --depth 1)
        GIT_PROGRESS TRUE # show download progress in Ninja
        USES_TERMINAL_DOWNLOAD TRUE)
FetchContent_MakeAvailable(doctest)


add_executable(my_tests SymbolTableTests.cpp
        ../benchmark/benchmarks.cpp)
#target_link_libraries(olTableTests PRIVATE your_library_target)
target_link_libraries(my_tests PRIVATE doctest::doctest)

add_test(NAME SymbolTableTests COMMAND SymbolTableTests)