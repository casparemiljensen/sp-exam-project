#ifndef EXPONENTIAL_DECAY_HPP
#define EXPONENTIAL_DECAY_HPP
#include "simulator.hpp"
#include "vessels.hpp"

namespace StochasticSimulation::Examples {
    Vessel exponential_decay(uint32_t q_a, uint32_t q_b, uint32_t q_c) {
        auto v = Vessel{"Exponential Decay"};

        constexpr auto rate = 0.001;
        const auto A = v.add("A", q_a);
        const auto B = v.add("B", q_b);
        const auto C = v.add("C", q_c);

        v.add((A + C) >> rate >>= B + C);
        return v;
    }
    std::vector<SimulationState> run_exponential_decay(uint32_t q_a, uint32_t q_b, uint32_t q_c) {
        auto vessel = exponential_decay(q_a, q_b, q_c);
        auto state = vessel.createSimulationState();

        //Observer version of simulate
        //auto test = [&trajectory2](const SimulationState& state) { trajectory2.emplace_back(state); };
        //Simulator::simulate(1500, c, covid, test);

        //Lazy evaluation version of simulate
        std::vector<SimulationState> trajectory;
        for (auto&& simState : Simulator::simulate_lazy(1500, state, vessel)) { // Consume
            trajectory.emplace_back(simState);
        }

        return trajectory;
    }

    // Requirement 5: Demonstrate the application of the library on the three examples
    std::vector<SimulationState> run_exponential_decay_a() {
        return run_exponential_decay(100, 0, 1);
    }
    std::vector<SimulationState> run_exponential_decay_b() {
        return run_exponential_decay(100, 0, 2);
    }
    std::vector<SimulationState> run_exponential_decay_c() {
        return run_exponential_decay(50, 50, 1);
    }
}

#endif //EXPONENTIAL_DECAY_HPP
