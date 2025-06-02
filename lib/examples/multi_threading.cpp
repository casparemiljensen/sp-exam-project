#include "charter.hpp"
#include "covid-19.hpp"
#include "multithreading.hpp"
namespace StochasticSimulation::Examples {
    void getPeakAverage(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns) {
        auto observer = [](const SimulationState& state) -> int {
            thread_local int peakH = 0;
            int currentH = state.species.get("H").quantity;
            if (currentH > peakH)
                peakH = currentH;
            return peakH;
        };

        auto reducer = [](const std::vector<int>& peaks) -> void { // Get average using reducer
            int total = 0;
            for (int peak : peaks) {
                total += peak;
            }
            float average = static_cast<float>(total) / peaks.size();
            std::cout << "Average sum(" << total << "," << peaks.size() << ") peak H: " << average << "\n";
        };

        Multithreading::runObserveReduce<int, void>( //<ObserverReturnType, reducerReturnType>
            endtime, baseVessel, observer, reducer, numberOfRuns
        );
    }

    void get_peak_average_serial(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns) {
        int peakH = 0;
        auto peak_serial_observer = [&peakH](const SimulationState& state) {
            if  (state.species.get("H").quantity > peakH)
                peakH = state.species.get("H").quantity;
            return peakH;
        };

        auto peak_vessel_serial = baseVessel;
        std::vector<int> peaks_serial;
        for (int i = 0; i < numberOfRuns; i++) {
            peakH = 0;
            auto vessel_serial = peak_vessel_serial;
            auto state_serial = peak_vessel_serial.createSimulationState();
            peaks_serial.emplace_back(Simulator::simulate_observer<int>(endtime, state_serial, vessel_serial, peak_serial_observer));
        }

        int sum = 0;
        for (int a : peaks_serial)
            sum += a;
        float average = static_cast<float>(sum) / peaks_serial.size();
        std::cout << "Average sum(" << sum <<") serial Peak: " << average << std::endl;
    }
}