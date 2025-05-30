#include "../include/charter.hpp"


#include "trajectory_chart_widget.hpp"

namespace StochasticSimulation {
    void Charter::showChart(std::vector<SimulationState> trajectory, u_int32_t width, u_int32_t height, const QString& title) {
        auto* chartWidget = new TrajectoryChartWidget(); // top-level-window
        chartWidget->setAttribute(Qt::WA_DeleteOnClose); // Safe auto-deletion on close - no memory leaks (since we use new and make it top-level with no parent)

        // TrajectoryChartWidget chartWidget;
        chartWidget->setTrajectory(trajectory);
        chartWidget->resize(width, height);
        chartWidget->setWindowTitle(title);
        chartWidget->show();
    }
} // StochasticSimulation