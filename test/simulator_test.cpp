#include <doctest/doctest.h>

#include "species.hpp"
#include "simulator.hpp"
#include "state.hpp"
#include "vessels.hpp"

using namespace StochasticSimulation;

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, pretty-printing reaction rules, etc).

TEST_CASE("Reactant_quantity_larger_than_zero_test") {
        // auto v = Vessel("Test");
        // const auto& A = v.add("A", 0);
        // const auto& B = v.add("B", 0);
        // const auto& C = v.add("C", 0);
        // SimulationState state = v.createSimulationState();
        //
        // SUBCASE("All reactants positive and present in state") {
        //         Reaction r({A, B}, {}, 0.1);
        //         state.species.get("A")._quantity = 5;
        //         state.species.get("B")._quantity = 5;
        //         CHECK(sim.allReactantsQuantitiesLargerThanZero(r, state));
        // }
}