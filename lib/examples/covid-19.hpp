#ifndef COVID_19_HPP
#define COVID_19_HPP

// Include necessary headers for the declaration.
#include "vessels.hpp"
#include <cstdint> // For uint32_t

namespace StochasticSimulation::Examples {
    // Declare the function. Remove 'inline'.
    Vessel seihr(uint32_t N);
} // namespace StochasticSimulation::Examples

#endif // COVID_19_HPP