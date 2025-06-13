#include "../include/charter.hpp"
#include "trajectory_chart_widget.hpp"

namespace StochasticSimulation {
    void Charter::showChart(std::vector<SimulationState> trajectory, uint32_t width, uint32_t height, const QString& title) {
        auto* chartWidget = new TrajectoryChartWidget();
        chartWidget->setAttribute(Qt::WA_DeleteOnClose);

        chartWidget->setTrajectory(trajectory);
        chartWidget->resize(width, height);
        chartWidget->setWindowTitle(title);
        chartWidget->show();
    }
} // StochasticSimulation