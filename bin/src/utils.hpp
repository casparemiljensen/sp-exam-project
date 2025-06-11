#ifndef UTILS_HPP
#define UTILS_HPP

#include "utils.hpp"
#include <filesystem>
#include <fstream>

#include "vessels.hpp"

namespace fs = std::filesystem;

inline fs::path find_project_root() {
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


inline void generate_dot_file(StochasticSimulation::Vessel &ves, const std::string &name) {
    fs::path out_path = find_project_root() / "graphs" / ("network_" + name + ".dot");
    std::cout << out_path.string() << std::endl;

    std::ofstream out_file{out_path};
    if (!out_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + out_path.string());
    }
    out_file << to_dot_network(ves.get_reactions(), ves.get_species()) << std::endl;
    out_file.close();
}

#endif // UTILS_HPP
