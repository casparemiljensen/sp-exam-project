#include "simulator.hpp"

#include <chrono>
#include <vector>
#include "vessels.hpp"
#include "state.hpp"

class simulator {
    std::vector<Reaction> reactions;
    std::vector<Species> species;


public:


    /* INPUT
     *  - reactions: from field
     *  - endtime: from params
     *  - simulationstate: from params
     *      - with amount Qi of reactant i
     */


    void simulate(float endtime, SimulationState state)
    {
        // Each time the simulation advances:
            // trajectory.push_back({current_time, species});

        float t = 0;

        while (t < endtime) {
            for (auto& reaction : reactions) {
                // for each reaction compute delay
                reaction.calculateDelay();
            }
            const auto r = getSmallestDelay();
            t += r.delay;

            if (!allReactantsQuantitiesLargerThanZero(r))
                continue;

            for (auto& species : r.reactants) {
                species->quantity -= 1;
            }
            // For each reactant
            for (auto& product : r.products) {
                product->quantity += 1;
            }
        }

        // Print/store/observe the state Qi

    }

    // For smallest reaction (reaction with smallest delay) all reactants (species) must have a quantity of x>0 (otherwise they can't create a reaction)


    bool allReactantsQuantitiesLargerThanZero(const Reaction& reaction) {
        for (auto& species : reaction.reactants) {
            if (species->quantity <= 0)
                return false;
        }
        return true;
    }


    const Reaction& getSmallestDelay() {
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