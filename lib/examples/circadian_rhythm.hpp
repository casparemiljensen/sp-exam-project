#ifndef CIRCADIAN_RHYTH_HPP
#define CIRCADIAN_RHYTH_HPP

#include "simulator.hpp"
#include "vessels.hpp"
#include "../../bin/src/utils.hpp"

namespace StochasticSimulation::Examples {
    Vessel circadian_rhythm ();
    std::vector<SimulationState> run_circadian_sim();

}

#endif //CIRCADIAN_RHYTH_HPP