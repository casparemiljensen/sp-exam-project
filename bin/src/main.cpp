#include <iostream>
#include <sstream>
#include <fstream>
#include <QApplication>

#include "charter.hpp"
#include "utils.hpp"
#include "trajectory_chart_widget.hpp"

#include "covid-19.hpp"
#include "multithreading.hpp"
#include "exponential_decay.hpp"
#include "circadian_rhythm.hpp"

using namespace StochasticSimulation;
namespace fs = std::filesystem;

void runSimulations(float endtime, Vessel &baseVessel);

// Finds the project root by lookSing at either a .git or CMakeLists.txt
// Prioritizes to find .git.
// Falls back to the topmost CMakeLists.txt if not .git is found.

// fs::path find_project_root() {
//     fs::path current = fs::current_path();
//     fs::path last_with_cmake;
//
//     while (!current.empty()) {
//         if (fs::exists(current / ".git")) {
//             return current;
//         }
//         if (fs::exists(current / "CMakeLists.txt")) {
//             last_with_cmake = current;
//         }
//         current = current.parent_path();
//     }
//
//     if (!last_with_cmake.empty()) {
//         return last_with_cmake;
//     }
//     throw std::runtime_error("Project root not found (no .git or CMakeLists.txt).");
// }

// void generate_covid_network_dot_file(auto &covid) {
//     fs::path out_path = find_project_root() / "graphs" / "network.dot";
//     std::cout << out_path.string() << std::endl;
//     std::ofstream out_file{out_path};
//
//     if (!out_file.is_open()) {
//         throw std::runtime_error("Failed to open file: " + out_path.string());
//     }
//     out_file << to_dot_network(covid.get_reactions(), covid.get_species()) << std::endl;
//     out_file.close();
// }

// void generate_dot_file(const auto& model, const std::string& name) {
//     fs::path out_path = find_project_root() / "graphs" / "network_"(name + ".dot");
//     std::cout << out_path.string() << std::endl;
//
//     std::ofstream out_file{out_path};
//     if (!out_file.is_open()) {
//         throw std::runtime_error("Failed to open file: " + out_path.string());
//     }
//     out_file << to_dot_network(model.get_reactions(), model.get_species()) << std::endl;
//     out_file.close();
// }


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Requirement 7 ...To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
    // without storing an entire trajectory. Record the peak hospitalization values for population sizes of NNJ and NDK.
    //Examples::estimate_peak_hospitalized();

    // Requirement 5: Demonstrate the application of the library on the three examples

    // Example 1: Exponential Decay
    auto exponential_decay_a = Examples::run_exponential_decay_a();
    auto exponential_decay_b = Examples::run_exponential_decay_b();
    auto exponential_decay_c = Examples::run_exponential_decay_c();
    Charter::showChart(exponential_decay_a, 800, 600, "exponential_decay_a");
    Charter::showChart(exponential_decay_b, 800, 600, "exponential_decay_b");
    Charter::showChart(exponential_decay_c, 800, 600, "exponential_decay_c");

    // generate_dot_file(exponential_decay_a, "exponential_decay_a");
    // generate_dot_file(exponential_decay_b, "exponential_decay_b");
    // generate_dot_file(exponential_decay_c, "exponential_decay_c");


    // Example 2: Circadian Rhythm
    Examples::run_circadian_sim();


    // Example 3: Covid 19

        // Create chart widget and set data
    auto covid_sim = Examples::run_covid_sim();
    Charter::showChart(covid_sim, 800, 600, "covid_sim");

    // auto covid = Examples::seihr(20000);
    // generate_covid_network_dot_file(covid);



    // auto covid = Examples::seihr(20000);
    // generate_covid_network_dot_file(covid);
    //
    // Examples::estimate_peak_hospitalized();
    //
    // // Create chart widget and set data
    // auto traj = Examples::run_covid_sim();
    //
    // std::cout << "Test " << std::endl;
    //
    // Charter::showChart(traj, 800, 600, "Test");


    return app.exec();
}
