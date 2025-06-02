#include "charter.hpp"
#include "covid-19.hpp"
#include "multi_threading.hpp"
namespace StochasticSimulation::Examples {
    void get_peak_average(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns) {
        auto observer = [](const SimulationState& state) -> int {
            thread_local int peakH = 0;
            int currentH = state.species.get("H").quantity;
            if (currentH > peakH)
                peakH = currentH;
            return peakH;
        };

        auto peaks = Multithreading::runObserve<int>( //<ObserverReturnType>
            endtime, baseVessel, observer, numberOfRuns
        );

        int sum = 0;
        for (const auto& peak : peaks) {
            sum += peak;
        }

        float average = static_cast<float>(sum) / peaks.size();
        std::cout << "Average sum(" << sum <<") Peak: " << average << std::endl;
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