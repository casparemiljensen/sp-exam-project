#include "multithreading.hpp"
//
// Created by wired on 5/30/25.
//
namespace StochasticSimulator::Examples {
    void getPeakAverage(float endtime, StochasticSimulation::Vessel& baseVessel, const u_int32_t numberOfRuns) {
        auto observer = [](const StochasticSimulation::SimulationState& state) -> int {
            thread_local int peakH = 0;
            int currentH = state.species.get("H").quantity;
            if (currentH > peakH) peakH = currentH;
            return peakH;
        };

        auto reducer = [](const std::vector<int>& peaks) -> void { // Get average using reducer
            int total = 0;
            for (int peak : peaks) {
                total += peak;
            }
            float average = static_cast<float>(total) / peaks.size();
            std::cout << "Average peak H: " << average << "\n";
        };

        StochasticSimulation::Multithreading::runObserveReduce<int, void>( //<ObserverReturnType, reducerReturnType>
            endtime, baseVessel, observer, reducer, numberOfRuns
        );
    }
}