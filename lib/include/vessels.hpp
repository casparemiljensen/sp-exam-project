#ifndef VESSELS_HPP
#define VESSELS_HPP

#include <string>
#include <utility>
#include <vector>

#include "symbol_table.hpp"
#include "reaction.hpp"
#include "state.hpp"

namespace StochasticSimulation {
    class Vessel {
        // Requirement 3: Demonstrate the usage of the symbol table with the reactants (names and initial counts).
        SymbolTable<std::string, Species> species;
        std::vector<Reaction> reactions;
        std::string name = "Vessel";
        Species _env = Species("env");

    public:
        explicit Vessel(std::string name) : name(std::move(name)) {
        }

        Species add(const std::string &name, double amount) {
            return species.add(name, Species(name, amount));
        }

        void add(const Reaction reaction) {
            reactions.push_back(reaction);
        }

        Species environment() {
            species.add(_env.name, _env);
            return _env;
        }

        std::vector<Reaction>& get_reactions() {
            return reactions;
        }

        std::vector<Species> get_species() {
            return species.getValues();
        }

        SimulationState createSimulationState() {
            auto a = species;
            return SimulationState(species);
        }

        // Requirement 2: Provide pretty-printing of the reaction network in a) human readable format and b) network graph
        void prettyPrintReactions(bool printHeader = true) const {
            if (printHeader) {
                std::cout << name << ":\n";
            }
            for (const auto& reaction: reactions) {
                std::cout << reaction.to_string() << std::endl;
            }
        }
    };
}
#endif // VESSELS_HPP
