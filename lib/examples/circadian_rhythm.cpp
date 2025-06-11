#ifndef CIRCADIAN_RHYTHM_HPP
#define CIRCADIAN_RHYTHM_HPP

#include "simulator.hpp"
#include "vessels.hpp"
#include "../../bin/src/utils.hpp"

namespace StochasticSimulation::Examples {
    Vessel circadian_rhythm()
    {
        constexpr auto alphaA = 50;
        constexpr auto alpha_A = 500;
        constexpr auto alphaR = 0.01;
        constexpr auto alpha_R = 50;
        constexpr auto betaA = 50;
        constexpr auto betaR = 5;
        constexpr auto gammaA = 1;
        constexpr auto gammaR = 1;
        constexpr auto gammaC = 2;
        constexpr auto deltaA = 1;
        constexpr auto deltaR = 0.2;
        constexpr auto deltaMA = 10;
        constexpr auto deltaMR = 0.5;
        constexpr auto thetaA = 50;
        constexpr auto thetaR = 100;
        auto v = Vessel{"Circadian Rhythm"};
        const auto env = v.environment();
        const auto DA = v.add("DA", 1);
        const auto D_A = v.add("D_A", 0);
        const auto DR = v.add("DR", 1);
        const auto D_R = v.add("D_R", 0);
        const auto MA = v.add("MA", 0);
        const auto MR = v.add("MR", 0);
        const auto A = v.add("A", 0);
        const auto R = v.add("R", 0);
        const auto C = v.add("C", 0);
        v.add((A + DA) >> gammaA >>= D_A);
        v.add(D_A >> thetaA >>= DA + A);
        v.add((A + DR) >> gammaR >>= D_R);
        v.add(D_R >> thetaR >>= DR + A);
        v.add(D_A >> alpha_A >>= MA + D_A);
        v.add(DA >> alphaA >>= MA + DA);
        v.add(D_R >> alpha_R >>= MR + D_R);
        v.add(DR >> alphaR >>= MR + DR);
        v.add(MA >> betaA >>= MA + A);
        v.add(MR >> betaR >>= MR + R);
        v.add((A + R) >> gammaC >>= C);
        v.add(C >> deltaA >>= R);
        v.add(A >> deltaA >>= env);
        v.add(R >> deltaR >>= env);
        v.add(MA >> deltaMA >>= env);
        v.add(MR >> deltaMR >>= env);
        return v;
    }

    std::vector<SimulationState> run_circadian_sim() {
        auto vessel = circadian_rhythm();
        auto state = vessel.createSimulationState();

        //Observer version of simulate
        //auto test = [&trajectory2](const SimulationState& state) { trajectory2.emplace_back(state); };
        //Simulator::simulate(1500, c, covid, test);

        //Lazy evaluation version of simulate

        std::vector<SimulationState> trajectory;
        for (auto&& simState : Simulator::simulate_lazy(1500, state, vessel)) { // Consume
            trajectory.emplace_back(simState);
        }
        generate_dot_file(vessel,"Circadian-Rhythm-Dot-Graph");
        return trajectory;
    }
}
#endif //CIRCADIAN_RHYTHM_HPP
