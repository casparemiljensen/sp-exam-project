#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <functional>
#include <generator>
#include <limits>

#include "state.hpp"
#include "trajectory_logger.hpp"
#include "vessels.hpp"

#pragma once

namespace StochasticSimulation
{
    class Simulator
    {
    public:
        // Requirement 4: Implement the stochastic simulation (Alg. 1) of the system using the reaction rules.

        // Requirement 7: ...provide a lazy trajectory generation interface (coroutine)...
        static std::generator<SimulationState> simulate_lazy(float endtime, SimulationState& state, Vessel vessel, int resolutionAmount = 1);

        // Implements observer


        // Requirement 7: Implement a generic support for (any) user-supplied state observer function object
        // The observer itself should be part by the user/test program and not part of the library.

        // Template can only reside in header files
        template <class observerReturnType>
        static observerReturnType simulate_observer(
            float endtime, SimulationState& state, Vessel vessel,
            const std::function<observerReturnType(SimulationState)>& observer = [](SimulationState state) {
                return 0;
            })
        {
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
                    state.species.get(species.name).decrease_quantity();
                }
                for (auto& product : r.products) {
                    state.species.get(product.name).increase_quantity();
                }

                // Record the current time and snapshot of all species quantities into the trajectory log
                result = observer(state);
            }
            return result;
        }

        // Implements observer

        // Requirement 7: Implement a generic support for (any) user-supplied state observer function object
        // The observer itself should be part by the user/test program and not part of the library.
        template <class observerReturnType>
        static observerReturnType simulate_observer_optimized(
            float endtime, SimulationState& state, Vessel vessel,
            const std::function<observerReturnType(SimulationState)>& observer)
        {
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
                    state.species.get(species.name).decrease_quantity();
                }
                for (auto& product : r.products) {
                    state.species.get(product.name).increase_quantity();
                }

                result = observer(state);
            }
            return result;
        }

    private:
        static bool allReactantsQuantitiesLargerThanZero(const Reaction& reaction, const SimulationState& state);

        static const Reaction& getSmallestDelay(Vessel& vessel);
    };
}  // namespace StochasticSimulation

#endif  // SIMULATOR_HPP
