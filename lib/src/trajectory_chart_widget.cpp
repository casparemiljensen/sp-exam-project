#include "trajectory_chart_widget.hpp"

#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <oneapi/tbb/detail/_exception.h>

#include "state.hpp"

namespace StochasticSimulation {
    TrajectoryChartWidget::TrajectoryChartWidget(QWidget* parent)
        : QWidget(parent),
          chart_(new QChart()),
          chartView_(new QChartView(chart_, this))
    {
        auto layout = new QVBoxLayout(this);
        layout->addWidget(chartView_);
        setLayout(layout);

        setupChart();
    }

    void TrajectoryChartWidget::setupChart()
    {
        chart_->setTitle("Species Quantities Over Time");
        chart_->legend()->setVisible(true);
        chart_->legend()->setAlignment(Qt::AlignBottom);

        // Configure axes
        auto axisX = new QValueAxis;
        axisX->setTitleText("Time");
        axisX->setLabelFormat("%.1f");
        chart_->addAxis(axisX, Qt::AlignBottom);

        auto axisY = new QValueAxis;
        axisY->setTitleText("Quantity");
        axisY->setLabelFormat("%d");
        chart_->addAxis(axisY, Qt::AlignLeft);
    }

    void TrajectoryChartWidget::setTrajectory(const std::vector<SimulationState>& trajectory)
    {
        if (trajectory.empty())
            return;

        // Clear previous series
        for (auto& [name, series] : seriesMap_) {
            chart_->removeSeries(series);
            delete series;
        }
        seriesMap_.clear();

        // Get all species names from first time step (assumed consistent)
        const auto& firstStep = trajectory.front();
        for (const auto& [speciesName, _] : firstStep.species) {
            auto series = new QLineSeries();
            series->setName(QString::fromStdString(speciesName));
            chart_->addSeries(series);
            seriesMap_[speciesName] = series;

            // Attach axes
            series->attachAxis(chart_->axisX());
            series->attachAxis(chart_->axisY());
        }

        // Fill series with points from trajectory
        for (const auto& step : trajectory) {
            for (const auto& [speciesName, quantity] : step.species) {
                auto it = seriesMap_.find(speciesName);
                if (it != seriesMap_.end()) {
                    it->second->append(step.time, quantity._quantity);
                }
            }
        }

        // Adjust axes range
        auto axisX = static_cast<QValueAxis*>(chart_->axisX());
        auto axisY = static_cast<QValueAxis*>(chart_->axisY());

        axisX->setRange(0, trajectory.back().time);

        // Find max quantity for Y axis
        int maxQuantity = 0;
        for (const auto& step : trajectory) {
            for (const auto& [_, quantity] : step.species) {
                if (quantity._quantity > maxQuantity)
                    maxQuantity = quantity._quantity;
            }
        }
        axisY->setRange(0, maxQuantity + 1);

        chartView_->repaint();
    }

    void TrajectoryChartWidget::setTrajectory(std::vector<std::vector<double>>& data, std::vector<std::string>& names) {
        // Clear previous series

        if (data.size() != names.size() + 1)
            return; //Todo: Throw
        for (auto& [name, series] : seriesMap_) {
            chart_->removeSeries(series);
            delete series;
        }
        seriesMap_.clear();

        // Get all species names from first time step (assumed consistent)
        for (const auto& speciesName : names) {
            auto series = new QLineSeries();
            series->setName(QString::fromStdString(speciesName));
            chart_->addSeries(series);
            seriesMap_[speciesName] = series;

            // Attach axes
            series->attachAxis(chart_->axisX());
            series->attachAxis(chart_->axisY());
        }
        double maxQuantity = 0;
        // Fill series with points from trajectory
        for (int x = 1; x < data.size(); x++) {
            for (int i = 0; i < data[x].size(); ++i) {
                auto it = seriesMap_.find(names[x-1]);
                if (it != seriesMap_.end()) {
                    if (maxQuantity < data[x][i])
                        maxQuantity = data[x][i];
                    it->second->append(data.front().at(i), data[x][i]);
                }
            }
        }


        // Adjust axes range
        auto axisX = static_cast<QValueAxis*>(chart_->axisX());
        auto axisY = static_cast<QValueAxis*>(chart_->axisY());

        axisX->setRange(0, data.front().back());
        axisY->setRange(0, maxQuantity + 1);

        chartView_->repaint();
    }


}
