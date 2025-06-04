include("../cmake/doctest.cmake")

add_executable(symbol_table_test symbol_table_test.cpp)
target_link_libraries(symbol_table_test PRIVATE doctest::doctest_with_main stochastic-simulation)
add_test(NAME symbol_table_test COMMAND symbol_table_test)

add_executable(another_one another_one.cpp)
target_link_libraries(another_one PRIVATE doctest::doctest_with_main stochastic-simulation)
add_test(NAME another_one COMMAND another_one)

add_executable(reaction_test reaction_test.cpp)
target_link_libraries(reaction_test PRIVATE doctest::doctest_with_main stochastic-simulation)
add_test(NAME reaction_test COMMAND reaction_test)