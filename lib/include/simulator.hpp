#ifndef SIMULATORE_HPP
#define SIMULATORE_HPP
#include "state.hpp"
#include "vessels.hpp"

#pragma once

namespace StochasticSimulation {

    class Simulator {
    public:
        static void simulate(float endtime, SimulationState& state, Vessel vessel, std::vector<TimeStep>& trajectory);

    private:
        static bool allReactantsQuantitiesLargerThanZero(const Reaction& reaction);

        static const Reaction& getSmallestDelay(Vessel& vessel);
    };

}
#endif //SIMULATORE_HPP