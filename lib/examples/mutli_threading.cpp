#include "multithreading.hpp"
//
// Created by wired on 5/30/25.
//
namespace StochasticSimulation::Examples {
    void getPeakAverage(float endtime, Vessel& baseVessel, const u_int32_t numberOfRuns) {
        auto observer = [](const SimulationState& state) {
            thread_local int peakH = 0;
            if  (state.species.get("H").quantity > peakH)
                peakH = state.species.get("H").quantity;
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

        Multithreading::runObserveReduce<int, void>( //<ObserverReturnType, reducerReturnType>
            endtime, baseVessel, observer, reducer, numberOfRuns
        );
    }
}