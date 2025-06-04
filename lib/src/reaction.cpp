#include <string>
#include <utility>
#include <vector>
#include "reaction.hpp"

#include <cmath>
#include <sstream>
#include <iostream>
#include <random>

#include "state.hpp"

namespace StochasticSimulation {
    
    bool Reaction::runningOptimized = false;

    Species::Species()
        : name(), _quantity(0) {
    }

    Species::Species(std::string name, int quantity)
        : name(std::move(name)), _quantity(quantity) {}

    //Reaction::Reaction(std::vector<Species> reactants, std::vector<Species> products, const double rate)
    //    : reactants(std::move(reactants)), products(std::move(products)), rate(rate) {}

    void Reaction::print() const {
        //myPrint(this->to_string());
    }

    std::string Reaction::to_string() const {
        std::string out;
        for (size_t i = 0; i < reactants.size(); i++) {
            out += reactants[i].to_string();
            if (i < reactants.size() - 1) out += " + ";
        }
        out += " --(" + std::to_string(rate) + ")--> ";
        for (size_t i = 0; i < products.size(); i++) {
            out += products[i].to_string();
            if (i < products.size() - 1) out += " + ";
        }
        return out;
    }

        // We have a list of reactants.. If they meet (rate), then produce a result (products).

        //Uses Vessel quantities as state, can be modified to use external state
    void Reaction::calculateDelay(SimulationState& state)
    {
        if (!shouldBeRecalculated && runningOptimized)
            return;

        int product = 1;
        for (const Species& sp : reactants) {
            product *= state.species.get(sp.name)._quantity;
        }

        double lambda = rate * product;
        if (lambda <= 0.0 || !std::isfinite(lambda)) {
            delay = std::numeric_limits<double>::infinity();
            return;
        }

        static std::mt19937 rng(std::random_device{}());
        std::exponential_distribution<> dist(lambda);
        delay = dist(rng);

        shouldBeRecalculated = false;
        //std::cout << "delay: " << delay << std::endl;
    }


    std::ostream& operator<<(std::ostream& os, const Species& s) {
        os << "Species(name=" << s.name << ")";
        return os;
    }

    Reaction operator+(const Species& a, const Species& b) {
        return Reaction({ a, b});
    }

    bool operator==(const Species& a, const Species& b) {
        return a.name == b.name && a._quantity == b._quantity;
    }

    // (A + B) + C → adds another Species to the list of reactants
    Reaction operator+(const Reaction& reaction, const Species& species) { // Er reaction pointer eller ikke?
        // reaction.reactants.push_back(species);
        // return reaction;

        std::vector<Species> new_reactants = reaction.reactants;
        new_reactants.push_back(species);
        return Reaction(new_reactants, reaction.products, reaction.rate);

    }

    // (A + B) >> 0.01 → sets the reaction rate     - intrinsic
    Reaction operator>>(const Reaction& reaction, const double rate) {
        return Reaction(reaction.reactants, reaction.products, rate);
    }

    Reaction operator>>(const Species& species, const double rate) {
        return Reaction({species},{}, rate);
    }

    Reaction operator>>(const Species& species, const int rate) {
        return Reaction({species},{}, rate);
    }

    //((A + B)) >> 0.01 >>= C → completes the reaction and creates a Reaction object
    Reaction operator>>=(const Reaction& reaction, const Species& product) {
        return Reaction{ reaction.reactants, { product }, reaction.rate };
    }

    Reaction operator>>=(const Reaction& reactionA, const Reaction& reactionB) {
        return Reaction{ reactionA.reactants, { reactionB.reactants }, reactionA.rate };
    }


    std::string to_dot(const Reaction& reaction, const int index) {
        std::ostringstream out;
        std::string rname = "r" + std::to_string(index);
        out << "  " << rname << " [label=\"λ=" << reaction.rate << "\",shape=\"oval\",fillcolor=\"yellow\",style=\"filled\"];\n";
        for (const auto& reactant : reaction.reactants) {
            out << "  " << reactant.name << " -> " << rname << ";\n";
        }
        for (const auto& product : reaction.products) {
            out << "  " << rname << " -> " << product.name << ";\n";
        }
        return out.str();
    }

    std::string to_dot(const Species& species) {
        std::ostringstream out;

        out << "  " << species.name << " [shape=\"rect\",fillcolor=\"cyan\",style=\"filled\"];\n";
        return out.str();
    }


    std::string to_dot_network(const std::vector<Reaction>& reactions, const std::vector<Species>& species) {
        std::ostringstream out;
        out << "digraph {\n";
        for (size_t i = 0; i < reactions.size(); ++i) {
            out << to_dot(reactions[i], static_cast<int>(i));
        }
        for (size_t i = 0; i < species.size(); ++i) {
            out << to_dot(species[i]);
        }
        out << "}\n";
        return out.str();
    }
}


