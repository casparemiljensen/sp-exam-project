//
// Created by wired on 5/30/25.
//

#ifndef MULTITHREADING_HPP
#define MULTITHREADING_HPP
#include <functional>
#include <future>

#include "simulator.hpp"
#include "state.hpp"
#include "vessels.hpp"

namespace StochasticSimulation {
    class Multithreading {
    public:
        template<class observerReturnType, class reducerReturnType> // generic
        static void runObserveReduce(
            float endtime,
            Vessel& baseVessel,
            const std::function<observerReturnType(SimulationState)>& observer,
            const std::function<reducerReturnType(const std::vector<observerReturnType>&)>& reducer,
            const u_int32_t numberOfRuns)
        {
            std::vector<std::future<observerReturnType>> futures; // futures = promises

            for (int i = 0; i < numberOfRuns; i++) {
                Vessel vesselCopy = baseVessel;
                SimulationState state = vesselCopy.createSimulationState();

                futures.emplace_back(std::async(std::launch::async,
                    [endtime, state = std::move(state), vesselCopy = std::move(vesselCopy), observer]() mutable { // TODO: Why mutable?
                        auto a = Simulator::simulate_observer<observerReturnType>(endtime, state, vesselCopy, observer); // Pass reserver into simulation, and return observer
                        return a;
                }));
            }

            std::vector<observerReturnType> observerResults; // Accumulate oberverResults in a vector
            for (auto& f : futures) {
                observerResults.emplace_back(f.get());
            }

            reducer(observerResults);
        }
    };
}
#endif //MULTITHREADING_HPP
