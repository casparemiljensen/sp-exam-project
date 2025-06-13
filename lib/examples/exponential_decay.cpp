#ifndef EXPONENTIAL_DECAY_HPP
#define EXPONENTIAL_DECAY_HPP

#include "simulator.hpp"
#include "vessels.hpp"
#include "../../bin/src/utils.hpp"

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
    std::vector<SimulationState> run_exponential_decay(Vessel vessel) {
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

    Vessel exponential_decay_a() {
        return exponential_decay(100, 0, 1);
    }
    Vessel  exponential_decay_b() {
        return exponential_decay(100, 0, 2);
    }
    Vessel  exponential_decay_c() {
        return exponential_decay(50, 50, 1);
    }

    // Requirement 5: Demonstrate the application of the library on the three examples
    std::vector<SimulationState> run_exponential_decay_a() {
        return run_exponential_decay(exponential_decay_a());
    }
    std::vector<SimulationState> run_exponential_decay_b() {
        return run_exponential_decay(exponential_decay_b());
    }
    std::vector<SimulationState> run_exponential_decay_c() {
        return run_exponential_decay(exponential_decay_c());
    }

    void generate_dot_graph_exponential_decay() {
        auto ves = Vessel{"Exponential Decay"};
        generate_dot_file(ves,"Exponential-Decay-Dot-Graph");
    }
}

#endif //EXPONENTIAL_DECAY_HPP
