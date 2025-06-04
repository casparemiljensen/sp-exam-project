#include "charter.hpp"
#include "covid-19.hpp"
#include "multi_threading.hpp"

#include "debug_print.hpp"

namespace StochasticSimulation::Examples {
    void get_peak_average(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns, const std::string& peakProperty) {
        auto observer = [&peakProperty](const SimulationState& state) -> int {
            thread_local int peak = 0;
            if (int currentProperty = state.species.get(peakProperty)._quantity; currentProperty > peak)
                peak = currentProperty;
            return peak;
        };

        auto peaks = Multithreading::runObserve<int>( //<ObserverReturnType>
            endtime, baseVessel, observer, numberOfRuns
        );

        int sum = 0;
        for (const auto& peak : peaks) {
            sum += peak;
        }

        float average = static_cast<float>(sum) / peaks.size();
        //std::cout << "Average sum(" << sum <<") Peak: " << average << std::endl;
    }

    void get_peak_average_serial(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns, const std::string& peakProperty) {
        int peak = 0;
        auto peak_serial_observer = [&peak, &peakProperty](const SimulationState& state) {
            const int currentProperty = state.species.get(peakProperty)._quantity;
            if  (currentProperty > peak)
                peak = currentProperty;
            return peak;
        };

        auto peak_vessel_serial = baseVessel;
        std::vector<int> peaks_serial;
        for (int i = 0; i < numberOfRuns; i++) {
            //debug_print("Starting run");
            peak = 0;
            auto vessel_serial = peak_vessel_serial;
            auto state_serial = peak_vessel_serial.createSimulationState();
            peaks_serial.emplace_back(Simulator::simulate_observer<int>(endtime, state_serial, vessel_serial, peak_serial_observer));
            //debug_print("Finished run");
        }

        int sum = 0;
        for (int a : peaks_serial)
            sum += a;
        float average = static_cast<float>(sum) / peaks_serial.size();
        //std::cout << "Average sum(" << sum <<") serial Peak: " << average << std::endl;
    }

    void get_peak_average_serial_optimized(float endtime, Vessel& baseVessel, const uint32_t numberOfRuns, const std::string& peakProperty) {
        int peak = 0;
        auto peak_serial_observer = [&peak, &peakProperty](const SimulationState& state) {
            const int currentProperty = state.species.get(peakProperty)._quantity;
            if  (currentProperty > peak)
                peak = currentProperty;
            return peak;
        };

        auto peak_vessel_serial = baseVessel;
        std::vector<int> peaks_serial;
        for (int i = 0; i < numberOfRuns; i++) {
            //debug_print("Starting run");
            peak = 0;
            auto vessel_serial = peak_vessel_serial;
            auto state_serial = peak_vessel_serial.createSimulationState();
            peaks_serial.emplace_back(Simulator::simulate_observer_optimized<int>(endtime, state_serial, vessel_serial, peak_serial_observer));
            //debug_print("Finished run");
        }

        int sum = 0;
        for (int a : peaks_serial)
            sum += a;
        float average = static_cast<float>(sum) / peaks_serial.size();
        //std::cout << "Average sum(" << sum <<") serial Peak: " << average << std::endl;
    }
}
