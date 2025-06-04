#ifndef VESSELS_HPP
#define VESSELS_HPP
#include <string>
#include <utility>

#include "symbol_table.hpp"
#include "reaction.hpp"
#include <vector>

#include "state.hpp"

namespace StochasticSimulation {
    class Vessel {
        SymbolTable<std::string, Species> species;
        std::vector<Reaction> reactions;
        std::string name = "Vessel";
        Species _env = Species("env");


    public:
        explicit  Vessel(std::string name) : name(std::move(name)) {}

        Species add(const std::string& name, double amount) {
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
            return SimulationState(species);
        }
    };





}
#endif // VESSELS_HPP
