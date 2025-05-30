//
// Created by wired on 5/30/25.
//

#include <thread>
#include <future>

#include "simulator.hpp"
#include "state.hpp"

namespace StochasticSimulation {
    class Multithreading {
        void run() {
            auto futures = std::vector<std::future<void>>();

            //futures.push_back(std::async(std::launch::async, StochasticSimulation::Simulator::simulate()))
        }
    };
}
