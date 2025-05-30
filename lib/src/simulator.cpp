#include "simulator.hpp"

#include <chrono>
#include <functional>
#include <vector>
#include <generator>
#include "vessels.hpp"
#include "state.hpp"

namespace StochasticSimulation {
    // Implements observer
    void Simulator::simulate(float endtime, SimulationState& state, Vessel vessel, const std::function<void(SimulationState)>& observer)
    {
        observer(state);
        // Each time the simulation advances:
            // trajectory.push_back({current_time, species});


        while (state.time < endtime) {
            for (auto& reaction : vessel.get_reactions()) {
                // for each reaction compute delay
                reaction.calculateDelay(state);
            }
            auto r = getSmallestDelay(vessel);
            if (r.delay == std::numeric_limits<double>::infinity()) {
                std::cout << "No valid reactions left — simulation stopping." << std::endl;
                break;
            }
            state.time += r.delay;

            if (!allReactantsQuantitiesLargerThanZero(r))
                continue;

            for (auto& species : r.reactants) {
                state.species.get(species.name).quantity -= 1;
            }
            // For each reactant
            for (auto& product : r.products) {
                state.species.get(product.name).quantity += 1;
            }
        }
    }

    // Implements Lazy evaluation through coroutine. Only works in version > c++ 23
    // Generator = C++ lazy evaluation (generates a sequence of elements by repeatedly resuming the coroutine from which it was returned.)
    std::generator<SimulationState> Simulator::simulate(float endtime, SimulationState &state, Vessel vessel)
    {
        // Yield initial state
        co_yield state;

        while (state.time < endtime) {
            for (auto& reaction : vessel.get_reactions()) {
                // for each reaction compute delay
                reaction.calculateDelay(state);
                //std::cout << "Updated reaction delay: " << reaction.delay << std::endl;
            }
            auto r = getSmallestDelay(vessel);
            if (r.delay == std::numeric_limits<double>::infinity()) {
                std::cout << "No valid reactions left — simulation stopping." << std::endl;
                break;
            }
            state.time += r.delay;

            // std::cout << "Selected reaction delay: " << r.delay << std::endl;
            // std::cout << "State time: " << state.time << std::endl;

            // std::cout << "Checking reactants for delay: " << r.delay << "\n";
            // for (const auto& species : r.reactants) {
            //     std::cout << "Reactant: " << species.name
            //               << ", quantity in reaction: " << species.quantity
            //               << ", quantity in state: " << state.species.get(species.name).quantity << "\n";
            // }

            // std::cout << "Before reaction:" << std::endl;
            // for (const auto& product : r.products) {
            //     auto& p = state.species.get(product.name);
            //     std::cout << "Product: " << product.name << ", quantity: " << p.quantity << std::endl;
            // }


            if (!allReactantsQuantitiesLargerThanZero(r, state))
                continue;

            for (auto& species : r.reactants) {
                state.species.get(species.name).quantity -= 1;
            }
            for (auto& product : r.products) {
                state.species.get(product.name).quantity += 1;
            }

            // Record the current time and snapshot of all species quantities into the trajectory log
            // Yield state amd only run next iteration when next state is required from calling entity (lazy evaluation)
            co_yield state;
        }
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
        if (reactions.empty()) {
            throw std::runtime_error("No reactions in vessel");
        }
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