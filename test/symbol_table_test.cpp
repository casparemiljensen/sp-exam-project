#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <memory>
#include <doctest/doctest.h>
#include "../lib/include/symbol_table.hpp"

using namespace StochasticSimulation;

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, pretty-printing reaction rules, etc).

TEST_CASE("SymbolTable basic functionality") {
    SymbolTable<std::string, int> table;

    SUBCASE("Add and get value") {
        table.add("foo", 42);
        CHECK(table.get("foo") == 42);
    }

    SUBCASE("Duplicate key throws") {
        table.add("bar", 123);
        CHECK_THROWS_AS(table.add("bar", 456), std::runtime_error);
    }

    SUBCASE("Missing key throws on get") {
        CHECK_THROWS_AS(table.get("missing"), std::out_of_range);
    }

    SUBCASE("Contains works correctly") {
        CHECK_FALSE(table.contains("x"));
        table.add("x", 7);
        CHECK(table.contains("x"));
    }

    SUBCASE("getValues returns all values") {
        table.add("a", 1);
        table.add("b", 2);
        auto values = table.getValues();
        CHECK(values.size() == 2);
        CHECK(std::find(values.begin(), values.end(), 1) != values.end());
        CHECK(std::find(values.begin(), values.end(), 2) != values.end());
    }
}

TEST_CASE("SymbolTable with complex types") {
    SymbolTable<std::string, std::unique_ptr<int> > complexTable;

    SUBCASE("Add and get unique_ptr") {
        //complexTable.add("ptr", std::make_unique<int>(42));
        //CHECK(*complexTable.get("ptr") == 42);
    }
}
