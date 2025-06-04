#ifndef SIMULATORE_HPP
#define SIMULATORE_HPP
#include <functional>
#include <generator>
#include "state.hpp"
#include "trajectory_logger.hpp"
#include "vessels.hpp"
#include <limits>

#pragma once

namespace StochasticSimulation {

    class Simulator {
    public:
        static std::generator<SimulationState> simulate(float endtime, SimulationState &state, Vessel vessel);

        // Implements observer

        // Run a stochastic chemical reaction simulation over time
        // Lets us plug in an observer function that monitors the simulation state
        // Return whatever the observer gives us (last return wins)

        template<class observerReturnType>
        static observerReturnType simulate_observer(float endtime, SimulationState& state, Vessel vessel, const std::function<observerReturnType(SimulationState)>& observer)
        {
            Reaction::runningOptimized = false;
            observerReturnType result{};
            observer(state);
            // Each time the simulation advances:
                // trajectory.push_back({current_time, species});


            while (state.time < endtime) {
                for (auto& reaction : vessel.get_reactions()) {
                    // for each reaction compute delay
                    reaction.calculateDelay(state);
                    //std::cout << "Updated reaction delay: " << reaction.delay << std::endl;
                }
                auto r = getSmallestDelay(vessel);
                if (r.delay == std::numeric_limits<double>::infinity()) {
                    //std::cout << "No valid reactions left — simulation stopping." << std::endl;
                    break;
                }
                state.time += r.delay;

                if (!allReactantsQuantitiesLargerThanZero(r, state))
                    continue;

                for (auto& species : r.reactants) {
                    state.species.get(species->name).decrease_quantity();
                }
                for (auto& product : r.products) {
                    state.species.get(product->name).increase_quantity();
                }

                // Record the current time and snapshot of all species quantities into the trajectory log
                result = observer(state);
            }
            return result;
        }

        // Implements observer

        // Differ only by how they tell Reaction to compute delays (optimized flag)

        template<class observerReturnType>
        static observerReturnType simulate_observer_optimized(float endtime, SimulationState& state, Vessel vessel, const std::function<observerReturnType(SimulationState)>& observer)
        {
            Reaction::runningOptimized = true;
            observerReturnType result{};
            observer(state);

            while (state.time < endtime) {
                for (auto& reaction : vessel.get_reactions()) {
                    reaction.calculateDelay(state);
                }
                auto r = getSmallestDelay(vessel);
                if (r.delay == std::numeric_limits<double>::infinity()) {
                    break;
                }
                state.time += r.delay;

                if (!allReactantsQuantitiesLargerThanZero(r, state))
                    continue;

                for (auto& species : r.reactants) {
                    state.species.get(species->name).decrease_quantity();
                }
                for (auto& product : r.products) {
                    state.species.get(product->name).increase_quantity();
                }

                result = observer(state);
            }
            return result;
        }
    private:
        static bool allReactantsQuantitiesLargerThanZero(const Reaction& reaction, const SimulationState& state);

        static const Reaction& getSmallestDelay(Vessel& vessel);
    };

}
#endif //SIMULATORE_HPP