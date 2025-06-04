#ifndef STATE_HPP
#define STATE_HPP
#include <unordered_map>
#include <string>

#include "reaction.hpp"
#include "species.hpp"
#include "symbol_table.hpp"

namespace StochasticSimulation {
    struct SimulationState {
        double time = 0.0;
        SymbolTable<std::string, Species> species;

        explicit SimulationState(SymbolTable<std::string, Species> species);

        // Requirement 2: Provide pretty-printing of the reaction network in a) human readable.
        std::string to_string();
    };
}
#endif //STATE_HPP