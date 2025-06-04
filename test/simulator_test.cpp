#include <doctest/doctest.h>

#include <simulator.hpp>
#include <cmath>

using namespace StochasticSimulation;

TEST_CASE("Reactant_quantity_larger_than_zero_test") {
        Simulator sim;
        SimulationState state;
        Species A("A", 1);
        Species B("B", 2);
        Species C("C", 3);

        SUBCASE("All reactants positive and present in state") {
                Reaction r({A, B}, {}, 0.1);
                state.species.set("A", 5);
                state.species.set("B", 20);
                CHECK(sim.allReactantsQuantitiesLargerThanZero(r, state));
        }
}