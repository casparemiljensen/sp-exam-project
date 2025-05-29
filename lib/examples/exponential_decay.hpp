#ifndef EXPONENTIAL_DECAY_HPP
#define EXPONENTIAL_DECAY_HPP

// Include necessary headers for the declaration.
#include "vessels.hpp"
#include <cstdint> // For uint32_t

namespace StochasticSimulation::Examples {
    Vessel exponential_decay(uint32_t q_a, uint32_t q_b, uint32_t q_c);
} // namespace StochasticSimulation::Examples

#endif // EXPONENTIAL_DECAY_HPP