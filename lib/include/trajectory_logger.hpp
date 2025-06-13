#ifndef TRAJECTORY_LOGGER_HPP
#define TRAJECTORY_LOGGER_HPP

#include <vector>
#include <unordered_map>
#include <string>

#include "symbol_table.hpp"
#include "species.hpp"

namespace StochasticSimulation {
    struct TimeStep {
        double time = 0.0;
        std::unordered_map<std::string, int> speciesQuantities;
    };

    class TrajectoryLogger {
    public:
        // Requirement 3: Demonstrate the usage of the symbol table with the reactants (names and initial counts).
        void log(const double time, const SymbolTable<std::string, Species>& speciesTable) {
            TimeStep step;
            step.time = time;

            for (const auto& species : speciesTable.getValues()) {
                step.speciesQuantities[species.name] = species._quantity;
            }

            trajectory_.emplace_back(std::move(step));
        }

        [[nodiscard]]
        const std::vector<TimeStep>& getTrajectory() const {
            return trajectory_;
        }

    private:
        std::vector<TimeStep> trajectory_;
    };

}

#endif // TRAJECTORY_LOGGER_HPP
