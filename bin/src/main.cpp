#include <iostream>
#include <sstream>
#include <fstream>

#include "circadian_rythm.hpp"
#include "covid-19.hpp"
#include "exponential_decay.hpp"
#include "multithreading.hpp"
#include "mutli_threading.hpp"
#include "simulator.hpp"

using namespace StochasticSimulation;

void runSimulations(float endtime, Vessel& baseVessel);

int main() {

    // Species A("A");
    // Species B("B");
    // Species C("C");
    //
    // Reaction r = A + B >> 0.01 >>= C;
    //
    // r.print();

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


    // std::string path = "/home/wired/dev/SP/sp-exam-project/";
    std::string path = "/Software/c++/sp-exam-project";
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
    auto vessel = Examples::seihr(20000);

    Examples::getPeakAverage(1500, vessel, 1);


    auto peak_vessel_serial = Examples::seihr(20000);
    auto peak_state_serial = peak_vessel_serial.createSimulationState();
    auto peak_serial_observer = [](const SimulationState& state) {
        thread_local int peakH = 0;
        if  (state.species.get("H").quantity > peakH)
            peakH = state.species.get("H").quantity;
        return peakH;
    };

    std::vector<int> peaks_serial;
    //Simulator::simulate(1500, c, covid, test);
    for (int i = 0; i < 100; i++) {
        auto vessel_serial = peak_vessel_serial;
        auto state_serial = peak_state_serial;
        peaks_serial.emplace_back(Simulator::simulate_observer<int>(1500, state_serial, vessel_serial, peak_serial_observer));
    }

    int sum = 0;
    for (int a : peaks_serial)
        sum += a;
    float average = static_cast<float>(sum) / peaks_serial.size();
    std::cout << "Average sum(" << sum <<") serial Peak: " << average << std::endl;
    // TrajectoryChartWidget chartWidget;
    // chartWidget.setTrajectory(traj);
    // chartWidget.resize(800, 600);
    // chartWidget.show();
    //chartWidget.show();
    return app.exec();

    // return 0;
}

