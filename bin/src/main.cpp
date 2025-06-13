#include <QApplication>

#include "charter.hpp"
#include "utils.hpp"
#include "trajectory_chart_widget.hpp"

#include "covid-19.hpp"
#include "exponential_decay.hpp"
#include "circadian_rhythm.hpp"

using namespace StochasticSimulation;
namespace fs = std::filesystem;

void runSimulations(float endtime, Vessel &baseVessel);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Requirement 7 ...To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
    // without storing an entire trajectory. Record the peak hospitalization values for population sizes of NNJ and NDK.
    Examples::estimate_peak_hospitalized();

    // Requirement 5: Demonstrate the application of the library on the three examples
    // Example 1: Exponential Decay
    auto exponential_decay_a = Examples::run_exponential_decay_a();
    auto exponential_decay_b = Examples::run_exponential_decay_b();
    auto exponential_decay_c = Examples::run_exponential_decay_c();
    Charter::showChart(exponential_decay_a, 800, 600, "exponential_decay_a");
    Charter::showChart(exponential_decay_b, 800, 600, "exponential_decay_b");
    Charter::showChart(exponential_decay_c, 800, 600, "exponential_decay_c");

    // Requirement 2 (b): Provide pretty-printing of the reaction network in a) human readable format and b) network graph
    // - note, "dot -Tpng <*.dot> -o <*.png>still needs to be executed in the "graphs" folder
    auto exponential_decay_vessel_a = Examples::exponential_decay_a();
    generate_dot_file(exponential_decay_vessel_a, "exponential_decay_a");


    // Example 2: Circadian Rhythm
    auto circadian_rhythm = Examples::run_circadian_sim();
    Charter::showChart(circadian_rhythm, 800, 600, "circadian_rhythm");

    // Example 3: Covid 19
    // Create chart widget and set data
    auto covid_sim = Examples::run_covid_sim();
    Charter::showChart(covid_sim, 800, 600, "covid_sim");

    // Requirement 2 (a): Provide pretty-printing of the reaction network in a) human readable format and b) network graph
    auto circadian_rhythm_vessel = Examples::circadian_rhythm();
    circadian_rhythm_vessel.prettyPrintReactions();

    return app.exec();
}
