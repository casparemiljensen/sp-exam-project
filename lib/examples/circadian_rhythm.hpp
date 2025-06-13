#ifndef CIRCADIAN_RHYTH_HPP
#define CIRCADIAN_RHYTH_HPP

#include "vessels.hpp"

namespace StochasticSimulation::Examples {
    Vessel circadian_rhythm ();
    std::vector<SimulationState> run_circadian_sim();

}

#endif //CIRCADIAN_RHYTH_HPP