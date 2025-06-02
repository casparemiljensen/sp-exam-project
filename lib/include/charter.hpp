
#ifndef CHARTER_HPP
#define CHARTER_HPP
#include <vector>

#include "state.hpp"
#include <QWidget>


namespace StochasticSimulation {

class Charter {
    public:
        static void showChart(std::vector<SimulationState>, uint32_t, uint32_t, const QString& title); // QString since implicitly shared (copy-on-write, thread-aware)
};

} // StochasticSimulation

#endif //CHARTER_HPP
