#include <chrono>
#include <functional>
#include <vector>
#include <generator>
#include "vessels.hpp"
#include "state.hpp"

#include "simulator.hpp"


namespace StochasticSimulation {
    // Implements Lazy evaluation through coroutine. Only works in version > c++ 23
    // Generator = C++ lazy evaluation (generates a sequence of elements by repeatedly resuming the coroutine from which it was returned.)
    std::generator<SimulationState> Simulator::simulate_lazy(float endtime, SimulationState &state, Vessel vessel, int resolution_amount)
    {
        // Yield initial state
        co_yield state;

        while (state.time < endtime) {
            for (auto& reaction : vessel.get_reactions()) {
                reaction.calculateDelay(state);
            }
            auto r = getSmallestDelay(vessel);
            if (r.delay == std::numeric_limits<double>::infinity()) {
                std::cout << "No valid reactions left - simulation stopping." << std::endl;
                break;
            }
            state.time += r.delay;


            if (!allReactantsQuantitiesLargerThanZero(r, state))
                continue;

            for (auto& species : r.reactants) {
                state.species.get(species.name).decrease_quantity(resolution_amount);
            }
            for (auto& product : r.products) {
                state.species.get(product.name).increase_quantity(resolution_amount);
            }

            // Record the current time and snapshot of all species quantities into the trajectory log
            // Yield state and only run next iteration when next state is required from calling entity (lazy evaluation)
            co_yield state;
        }
    }

    // For smallest reaction (reaction with smallest delay) all reactants (species) must have a quantity of x>0 (otherwise they can't create a reaction
    bool Simulator::allReactantsQuantitiesLargerThanZero(const Reaction& reaction, const SimulationState &state) {
        for (const auto& species: reaction.reactants) {
            if (species._quantity > 0 && state.species.get(species.name)._quantity <= 0)
                return false;
        }
        return true;
    }


    const Reaction &Simulator::getSmallestDelay(Vessel &vessel) {
        auto &reactions = vessel.get_reactions();  // Must be a reference!
        if (reactions.empty()) throw std::runtime_error("No reactions");

        Reaction* smallest = &reactions[0];
        for (auto& r : reactions) {
            if (r.delay < smallest->delay)
                smallest = &r;
        }
        return *smallest;
    }
};
