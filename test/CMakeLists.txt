include("../cmake/doctest.cmake")


add_executable(SymbolTableTests SymbolTableTests.cpp)
target_link_libraries(SymbolTableTests PRIVATE doctest::doctest_with_main)
add_test(NAME SymbolTableTests COMMAND SymbolTableTests)