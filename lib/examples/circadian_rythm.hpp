#ifndef CIRCADIAN_RYTHM_HPP
#define CIRCADIAN_RYTHM_HPP

// Include necessary headers for the declaration.
// We only need 'Vessel' to declare the function.
#include "vessels.hpp"

namespace StochasticSimulation::Examples {
    // Declare the function.
    // The 'inline' keyword should be removed from here.
    // 'inline' suggests to the compiler to put the definition in every translation unit,
    // which is exactly what leads to LNK2005 errors when the definition is in a header
    // that's included by multiple .cpp files.
    Vessel circadian_rhythm();
} // namespace StochasticSimulation::Examples

#endif // CIRCADIAN_RYTHM_HPP