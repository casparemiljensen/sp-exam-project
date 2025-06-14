#include <doctest/doctest.h>

#include "species.hpp"
#include "reaction.hpp"
#include "vessels.hpp"
#include <cmath>

using namespace StochasticSimulation;

// Requirement 9: Implement unit tests (e.g. test symbol table methods, their failure cases, pretty-printing reaction rules, etc).
TEST_CASE("Species_Test") {
    SUBCASE("Species Default Constructor") {
        Species s;
        CHECK(s.name.empty());
        CHECK(s._quantity == 0);
    }

    SUBCASE("Constructor with empty name") {
        Species s("", 10);
        CHECK(s.name.empty());
        CHECK(s._quantity == 10);
    }
}

TEST_CASE("Reaction_Test") {
    SUBCASE("Reaction get reactants test") {
        const std::vector<Species> reactants{};
        const std::vector<Species> products{Species{"agent_a", 0}, Species{"agent_b", 0}};
        constexpr double rate = 5.0;


        Reaction r(reactants, products, rate);

        for (std::size_t i = 0; i < r.reactants.size(); i++) {
            CHECK(r.reactants[i].name == reactants[i].name);
        }
    }

    SUBCASE("Reaction get products test") {
        const std::vector<Species> reactants{};
        const std::vector<Species> products{Species{"agent_a", 0}, Species{"agent_b", 0}};
        constexpr double rate = 5.0;

        Reaction r(reactants, products, rate);

        for (std::size_t i = 0; i < r.products.size(); i++) {
            CHECK(r.products[i].name == products[i].name);
        }
    }
}


TEST_CASE("Delay calculation") {
    // lambda = rate x product
    SUBCASE("Delay with positive lambda test") {
        auto vessel = Vessel("Name");
        SimulationState state = vessel.createSimulationState();
        state.species.add("A", Species{"A", 5});
        Species A{"A"};

        Reaction r({A}, {}, 2.0);

        r.calculateDelay(state);

        CHECK(r.delay >= 0.0);
        CHECK(std::isfinite(r.delay));
    }

    SUBCASE("Delay with zero quantity test") {
        auto vessel = Vessel("Name");
        SimulationState state = vessel.createSimulationState();
        state.species.add("A", Species{"A", 0});
        Species A{"A"};
        Reaction r({A}, {}, 2.0);
        r.calculateDelay(state);
        CHECK(std::isinf(r.delay));
    }
}

// Identical reactions should yield identical fingerprints
TEST_CASE("Fingerprint is consistent test") {
    Reaction r1({Species{"X"}, Species{"Y"}}, {Species{"Z"}}, 1.0);
    Reaction r2({Species{"X"}, Species{"Y"}}, {Species{"Z"}}, 1.0);
    CHECK(r1.createFingerprint() == r2.createFingerprint());
}


TEST_CASE("Fingerprint is unique test") {
    Reaction r1({Species{"X"}, Species{"Y"}}, {Species{"Z"}}, 1.0);
    Reaction r2({Species{"X"}, Species{"Y"}}, {Species{"Z"}}, 1.5);
    CHECK(r1.createFingerprint() != r2.createFingerprint());
}


TEST_CASE("Reaction operator overloads (DSL) test") {
    SUBCASE("Species + Species gives correct reactants") {
        Species A("A");
        Species B("B");
        Species C("C");

        Reaction r = A + B;

        CHECK(r.reactants.size() == 2);
        CHECK(r.reactants[0].name == "A");
        CHECK(r.reactants[1].name == "B");
    }

    SUBCASE("Adding species to reaction appends to reactants") {
        Species A("A");
        Species B("B");
        Species C("C");

        Reaction r1 = A + B;
        Reaction r2 = r1 + C;

        CHECK(r2.reactants.size() == 3);
        CHECK(r2.reactants[2].name == "C");
    }

    SUBCASE("Reaction >> product finalizes with correct product") {
        Species A("A");
        Species B("B");

        Reaction r = A >> 0.01 >>= B;

        CHECK(r.reactants.size() == 1);
        CHECK(r.reactants[0].name == "A");

        CHECK(r.products.size() == 1);
        CHECK(r.products[0].name == "B");

        CHECK(r.rate == doctest::Approx(0.01));
    }

    SUBCASE("to string returns expected format") {
        Species A("A");
        Species B("B");

        Reaction r = A + B >> 0.02 >>= B;

        std::string expected = "A + B   >>  (0.02)  >>= B";
        CHECK(r.to_string() == expected);
    }

    SUBCASE("to string returns expected format") {
        Species A("A");
        Species B("B");

        Reaction r = A + B >> 0.02 >>= B + A;

        std::string expected = "A + B   >>  (0.02)  >>= B + A";
        CHECK(r.to_string() == expected);
    }
}
