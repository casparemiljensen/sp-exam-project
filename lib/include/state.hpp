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
    };
}
#endif //STATE_HPP



// Example

// SimulationState {
//     .time = 12.5,
//     .species = {
//         {"S", 50},
//         {"I", 30},
//         {"R", 20}
//     }
// }