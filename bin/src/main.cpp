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
#include "multi_threading.hpp"
#include "simulator.hpp"
#include <filesystem>
#include <benchmark/benchmark.h>

using namespace StochasticSimulation;
namespace fs = std::filesystem;


void runSimulations(float endtime, Vessel& baseVessel);


// Finds the project root by looking at either a .git or CMakeLists.txt
// Prioritizes to find .git.
// Falls back to the topmost CMakeLists.txt if not .git is found.

fs::path find_project_root() {
    fs::path current = fs::current_path();
    fs::path last_with_cmake;

    while (!current.empty()) {
        if (fs::exists(current / ".git")) {
            return current;
        }
        if (fs::exists(current / "CMakeLists.txt")) {
            last_with_cmake = current;
        }
        current = current.parent_path();
    }

    if (!last_with_cmake.empty()) {
        return last_with_cmake;
    }
    throw std::runtime_error("Project root not found (no .git or CMakeLists.txt).");
}



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

    auto covid = Examples::seihr(20000);

    fs::path out_path = find_project_root() / "graphs" / "network.dot";
    std::cout << out_path.string() << std::endl;
    std::ofstream out_file{out_path};

    if (!out_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + out_path.string());
    }
    out_file << to_dot_network(covid.get_reactions(), covid.get_species()) << std::endl;
    out_file.close();


    Examples::estimate_peak_hospitalized();

    // Create chart widget and set data
    auto traj = Examples::run_covid_sim();

    //Requirement 8
    std::cout << "Test " << std::endl;

    Examples::get_peak_average_serial();

    Charter::showChart(traj, 800, 600, "Test");

    return app.exec();
}

