#ifndef COVID_19_HPP
#define COVID_19_HPP
#include <cmath>

#include "charter.hpp"
#include "simulator.hpp"
#include "vessels.hpp"

namespace StochasticSimulation::Examples {
    [[nodiscard]] Vessel seihr(uint32_t N)
    {
        auto v = Vessel{"COVID19 SEIHR: " + std::to_string(N)};
        auto eps = 0.0009; // initial fraction of infectious
        auto E0 = size_t(std::round(eps * N * 15)); // initial exposed
        auto I0 = size_t(std::round(eps * N)); // initial infectious
        auto S0 = N - I0 - E0; // initial susceptible
        auto R0 = 2.4; // initial basic reproductive number
        auto alpha = 1.0 / 5.1; // incubation rate (E -> I) ~5.1 days
        auto gamma = 1.0 / 3.1; // recovery rate (I -> R) ~3.1 days
        auto beta = R0 * gamma; // infection/generation rate (S+I -> E+I)
        auto P_H = 0.9e-3; // probability of hospitalization
        auto kappa = gamma * P_H * (1.0 - P_H); // hospitalization rate (I -> H)
        auto tau = 1.0 / 10.12; // removal rate in hospital (H -> R) ~10.12 days
        auto S = v.add("S", S0); // susceptible
        auto E = v.add("E", E0); // exposed
        auto I = v.add("I", I0); // infectious
        auto H = v.add("H", 0); // hospitalized
        auto R = v.add("R", 0); // removed/immune (recovered + dead)
        v.add((S + I) >> beta / N >>= E + I); // susceptible becomes exposed by infectious
        v.add(E >> alpha >>= I); // exposed becomes infectious
        v.add(I >> gamma >>= R); // infectious becomes removed
        v.add(I >> kappa >>= H); // infectious becomes hospitalized
        v.add(H >> tau >>= R); // hospitalized becomes removed
        return v;
    }

    std::vector<SimulationState> run_covid_sim() {
        auto vessel = seihr(100);
        auto state = vessel.createSimulationState();
        std::vector<SimulationState> trajectory;

        //Observer version of simulate
        //auto test = [&trajectory](const SimulationState& state) { trajectory.emplace_back(state); };
        //Simulator::simulate(1500, c, covid, test);

        //Lazy evaluation version of simulate
        for (auto&& simState : Simulator::simulate(1500, state, vessel)) { // Consume
            trajectory.emplace_back(simState);
        }

        return trajectory;
    }

    // Big covid sim, Req 7B
    void estimate_peak_hospitalized() { // Uses lazy evaluation with limited population sizes
        std::vector<std::pair<std::string, uint32_t>> regions = {
            {"NNJ", 10000},
            {"NDK", 20000}
        };

        std::vector<std::string> peaks;
        for (const auto& [region, population] : regions) {
            auto vessel = seihr(population);
            auto state = vessel.createSimulationState();
            int peak = 0;
            for (auto&& simState : Simulator::simulate(500.0, state, vessel)) {
                int currentH = simState.species.get("H")._quantity;
                if (currentH > peak) {
                    peak = currentH;
                }
            }
            peaks.emplace_back(
                "Peak hospitalized in " + region + " (population " + std::to_string(population) + ": " + std::to_string(peak));
        }
        std::cout << "Peak hospitalized in regions:\n";
        for (const auto& entry : peaks) {
            std::cout << "  - " << entry << "\n";
        }
    }





}

#endif //COVID_19_HPP
