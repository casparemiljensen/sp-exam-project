#include <iostream>
#include <utility>
#include "state.hpp"

namespace StochasticSimulation {
    SimulationState::SimulationState(SymbolTable<std::string, Species> species) : species(std::move(species)) {}
}