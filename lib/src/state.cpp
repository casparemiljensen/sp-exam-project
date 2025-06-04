#include <iostream>
#include <utility>
#include "state.hpp"

namespace StochasticSimulation {
    SimulationState::SimulationState(SymbolTable<std::string, Species> species) : species(std::move(species)) {}

    std::string SimulationState::to_string() {
        std::stringstream ss;
        ss << "CurrentTime: " << time << " Species:" << std::endl;
        for (const auto& species : species | std::views::values) {
            ss << "  " << species.to_string() << ": " << species._quantity << std::endl;
        }
        return ss.str();
    }
}