#include "trajectory_chart_widget.hpp"

#include <QtCharts/QValueAxis>
#include <QVBoxLayout>

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

    // Get all species names from first time step
    const auto& firstStep = trajectory.front();
    std::map<std::string, QVector<QPointF>> pointsMap;
    for (const auto& [speciesName, _] : firstStep.species) {
        if (speciesName == "env") continue; // Guard to avoid printing the "env"

        auto series = new QLineSeries();
        series->setName(QString::fromStdString(speciesName));
        chart_->addSeries(series);
        seriesMap_[speciesName] = series;
        series->attachAxis(chart_->axisX());
        series->attachAxis(chart_->axisY());
        pointsMap[speciesName].reserve(trajectory.size());
    }

    // Fill the QVector<QPointF> for each species
    for (const auto& step : trajectory) {
        for (const auto& [speciesName, quantity] : step.species) {
            pointsMap[speciesName].append(QPointF(step.time, quantity._quantity));
        }
    }

    // Bulk replace data in each series
    for (const auto& [speciesName, series] : seriesMap_) {
        series->replace(pointsMap[speciesName]);
    }

    // Set axes range
    auto axisX = static_cast<QValueAxis*>(chart_->axisX());
    auto axisY = static_cast<QValueAxis*>(chart_->axisY());

    axisX->setRange(0, trajectory.back().time);

    int maxQuantity = 0;
    for (const auto& step : trajectory) {
        for (const auto& [speciesName, quantity] : step.species) {
            if (speciesName == "env") continue; // Guard to avoid printing the "env"
            if (quantity._quantity > maxQuantity)
                maxQuantity = quantity._quantity;
        }
    }
    axisY->setRange(0, maxQuantity + 1);

    // Disable animations and antialiasing for performance
    chart_->setAnimationOptions(QChart::NoAnimation);
    chartView_->setRenderHint(QPainter::Antialiasing, false);

    chartView_->repaint();
}


}
