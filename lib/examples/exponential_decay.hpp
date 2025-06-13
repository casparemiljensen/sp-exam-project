#ifndef EXPONENTIAL_DECAY_HPP
#define EXPONENTIAL_DECAY_HPP

#include "vessels.hpp"

namespace StochasticSimulation::Examples {
    Vessel exponential_decay(uint32_t q_a, uint32_t q_b, uint32_t q_c);
    std::vector<SimulationState> run_exponential_decay_a();
    std::vector<SimulationState> run_exponential_decay_b();
    std::vector<SimulationState> run_exponential_decay_c();
    Vessel exponential_decay_a();
    Vessel exponential_decay_b();
    Vessel exponential_decay_c();
} // namespace StochasticSimulation::Examples

#endif // EXPONENTIAL_DECAY_HPP