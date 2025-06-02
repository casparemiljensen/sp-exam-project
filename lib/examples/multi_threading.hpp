#include "multithreading.hpp"

namespace StochasticSimulation::Examples {
    void getPeakAverage(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns);
    void get_peak_average_serial(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns);
}