#ifndef COVID_19_HPP
#define COVID_19_HPP

#include "vessels.hpp"
#include <cstdint> // For uint32_t

namespace StochasticSimulation::Examples {
    Vessel seihr(uint32_t N);
    std::vector<SimulationState> run_covid_sim();
    void estimate_peak_hospitalized();
} // namespace StochasticSimulation::Examples

#endif // COVID_19_HPP