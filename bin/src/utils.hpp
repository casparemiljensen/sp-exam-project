#ifndef UTILS_HPP
#define UTILS_HPP

#include "utils.hpp"
#include <filesystem>
#include <fstream>

#include "vessels.hpp"

namespace fs = std::filesystem;


// Find the project root. Defined by prefix of project name, and a CMakeLists.txt
inline fs::path find_project_root() {
    constexpr auto project_name_prefix = "sp-exam-project";
    fs::path current = fs::current_path();

    for (int max_depth = 20; max_depth > 0 && !current.empty(); --max_depth) {  // Max-depth: How far up we want to go.
        const auto folder_name = current.filename().string();

        if (folder_name.starts_with(project_name_prefix)) {
            if (fs::exists(current / "CMakeLists.txt")) {
                return current;
            }
        }
        current = current.parent_path();
    }
    throw std::runtime_error("Project root not found (based on project name prefix + CMakeLists.txt).");
}


inline void generate_dot_file(StochasticSimulation::Vessel &ves, const std::string &name) {
    try {
        fs::path out_path = find_project_root() / "graphs" / ("network_" + name + ".dot");
        std::cout << out_path.string() << std::endl;

        std::ofstream out_file{out_path};
        if (!out_file.is_open()) {
            throw std::runtime_error("Failed to open file: " + out_path.string());
        }
        out_file << to_dot_network(ves.get_reactions(), ves.get_species()) << std::endl;
        out_file.close();
    } catch (const std::exception& ex) {
        std::cerr << "[generate_dot_file] Error: " << ex.what() << std::endl;
        throw; // rethrow after logging
    }
}

#endif // UTILS_HPP
