#include <iostream>
#include <sstream>
#include <fstream>
#include <QApplication>

#include "charter.hpp"
#include "trajectory_chart_widget.hpp"

#include "circadian_rythm.hpp"
#include "covid-19.hpp"
#include "exponential_decay.hpp"
#include "multithreading.hpp"
#include "mutli_threading.hpp"
#include "simulator.hpp"

#include <benchmark/benchmark.h>


using namespace StochasticSimulation;

void runSimulations(float endtime, Vessel& baseVessel);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Species A("A"), B("B"), C("C"), D("D");

    // Test 1: Basic reaction A + B -> C
    Reaction r1 = (A + B) >> 0.01 >>= C;
    std::cout << "Reaction 1: ";
    r1.print();  // Expected: A + B --(0.01)--> C


    // Test 2: Add three reactants: A + B + C -> D
    Reaction r2 = (A + B + C) >> 0.05 >>= D;
    std::cout << "Reaction 2: ";
    r2.print();  // Expected: A + B + C --(0.05)--> D

    // Test 3: Single species reacts to another
    Reaction r3 = A >> 0.02 >>= B;
    std::cout << "Reaction 3: ";
    r3.print();  // Expected: A --(0.02)--> B

    // Test 3.5: Single species reacts to another
    Reaction r4 = A + B >> 0.02 >>= B + C;
    std::cout << "Reaction 3.5: ";
    r4.print();  // Expected: A --(0.02)--> B


    // Todo: move to own file
    std::string path = "E:\\GithubRepos\\sp-exam-project";
    // std::string path = "/home/wired/dev/SP/sp-exam-project/";
    // std::string path = "/Software/c++/sp-exam-project";
    std::ofstream out(path + "network.dot");
    //out << to_dot_network(circadian_rythm.get_reactions(), circadian_rythm.get_species()) << std::endl;
    //out << to_dot_network(vec, vect) << std::endl;
    out.close();


    Examples::estimate_peak_hospitalized();


    // Create chart widget and set data
    auto traj = Examples::run_covid_sim();
    //TrajectoryChartWidget chartWidget;
    //Charter::showChart(traj, 800, 600, "Covid Simulation Trajectory");

    //Requirement 8
    std::cout << "Test " << std::endl;

    Examples::get_peak_average_serial();

    Charter::showChart(traj, 800, 600, "Test");


    // TrajectoryChartWidget chartWidget;
    // chartWidget.setTrajectory(traj);
    // chartWidget.resize(800, 600);
    // chartWidget.show();
    //chartWidget.show();
    return app.exec();
}
