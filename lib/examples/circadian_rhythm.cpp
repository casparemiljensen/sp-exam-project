#ifndef CIRCADIAN_RHYTHM_HPP
#define CIRCADIAN_RHYTHM_HPP

#include "simulator.hpp"
#include "vessels.hpp"
#include "../../bin/src/utils.hpp"

namespace StochasticSimulation::Examples {
    Vessel circadian_rhythm()
    {
        const auto alphaA = 50;
        const auto alpha_A = 500;
        const auto alphaR = 0.01;
        const auto alpha_R = 50;
        const auto betaA = 50;
        const auto betaR = 5;
        const auto gammaA = 1;
        const auto gammaR = 1;
        const auto gammaC = 2;
        const auto deltaA = 1;
        const auto deltaR = 0.2;
        const auto deltaMA = 10;
        const auto deltaMR = 0.5;
        const auto thetaA = 50;
        const auto thetaR = 100;
        auto v = StochasticSimulation::Vessel{"Circadian Rhythm"};
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

        std::vector<SimulationState> trajectory;
        //Observer version of simulate
        // auto test = [&trajectory](const SimulationState& state) -> int { trajectory.emplace_back(state); return 0; };
        // Simulator::simulate_observer<int>(1500, state, vessel, test);

        //Lazy evaluation version of simulate

        int i = 0;
        for (auto&& simState : Simulator::simulate_lazy(3, state, vessel)) { // Consume
            trajectory.emplace_back(simState);
            //std::cout << "did run: " << i++ << std::endl;
            i++;
        }
        generate_dot_file(vessel,"Circadian-Rhythm-Dot-Graph");
        std::cout << trajectory.size() << '\n';
        return trajectory;
    }
}
#endif //CIRCADIAN_RHYTHM_HPP
