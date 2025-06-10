
#ifndef CHARTER_HPP
#define CHARTER_HPP
#include <vector>

#include "state.hpp"
#include <QWidget>


namespace StochasticSimulation {

    // Requirement 6 - Display simulation trajectories of how the amounts change. We use qtCharts
    class Charter {
        // QString since implicitly shared (copy-on-write, thread-aware)
        public:
            static void showChart(std::vector<SimulationState>, uint32_t, uint32_t, const QString& title);
    };

} // StochasticSimulation

#endif //CHARTER_HPP
