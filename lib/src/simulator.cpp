#include "simulator.hpp"

#include <chrono>
#include <vector>
#include "vessels.hpp"
#include "state.hpp"

namespace StochasticSimulation {
    void Simulator::simulate(float endtime, SimulationState state, Vessel vessel)
    {
        // Each time the simulation advances:
            // trajectory.push_back({current_time, species});

        float t = 0;

        while (t < endtime) {
            for (auto& reaction : vessel.get_reactions()) {
                // for each reaction compute delay
                reaction.calculateDelay();
            }
            auto r = getSmallestDelay(vessel);
            t += r.delay;

            if (!allReactantsQuantitiesLargerThanZero(r))
                continue;

            for (auto& species : r.reactants) {
                species.quantity -= 1;
            }
            // For each reactant
            for (auto& product : r.products) {
                product.quantity += 1;
            }
        }

        // Print/store/observe the state Qi

    }

        // For smallest reaction (reaction with smallest delay) all reactants (species) must have a quantity of x>0 (otherwise they can't create a reaction)


    bool Simulator::allReactantsQuantitiesLargerThanZero(const Reaction& reaction) {
        for (auto& species : reaction.reactants) {
            if (species.quantity <= 0)
                return false;
        }
        return true;
    }


    const Reaction& Simulator::getSmallestDelay(Vessel& vessel) {
        auto& reactions = vessel.get_reactions();
        const Reaction* smallestReaction = &reactions[0];
        double smallest = reactions[0].delay;

        for (const auto& reaction : reactions) {
            if (reaction.delay < smallest) {
                smallest = reaction.delay;
                smallestReaction = &reaction;
            }
        }
        return *smallestReaction;
    }
    // void simulateFrame()
};



// TASKS
// r.delay formula
// simulate algo
// SimulationState class





//
// class Simulator {
// public:
//     Simulator(std::unordered_map<std::string, int> init_state,
//               std::vector<Reaction> reactions)
//         : state(std::move(init_state)), reactions(std::move(reactions)) {}
//
//     std::vector<std::pair<double, std::unordered_map<std::string, int>>>
//     simulate(double end_time);
//
// private:
//     std::unordered_map<std::string, int> state;
//     std::vector<Reaction> reactions;
// };