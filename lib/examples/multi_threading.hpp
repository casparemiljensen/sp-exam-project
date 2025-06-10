#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H
#include "multithreading.hpp"


namespace StochasticSimulation::Examples {
    void get_peak_average(float endtime, Vessel& baseVessel, uint32_t numberOfRuns, const std::string&);
    void get_peak_average_serial(float endtime, Vessel& baseVessel, uint32_t numberOfRuns, const std::string&);
    void get_peak_average_serial_optimized(float endtime, Vessel& baseVessel, uint32_t numberOfRuns, const std::string&);

}
#endif