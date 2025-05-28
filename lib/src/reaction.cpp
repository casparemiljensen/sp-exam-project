#include <string>
#include <vector>
#include "reaction.hpp"

#include <cmath>
#include <sstream>
#include <iostream>

namespace StochasticSimulation {
    void myPrint(const std::string& s) {
        std::cout << s << std::endl;
    }

    struct Species {
        std::string name;
        mutable int quantity; // How many units of this species exist

        // Constructor to initialize a Species with its name
        explicit Species(std::string name, int quantity = 0) : name(std::move(name)), quantity(quantity) {}

        Species() : quantity(0) {}
    };


    struct Reaction { // Represents a reaction. E.g. A + C --(λ)--> B + C
        std::vector<Species> reactants; // B, C (output species)
        std::vector<Species> products; // B, C (output species)
        const double rate; //The rate λ describes the intrinsic probability of individuals meeting and reacting over one time unit.
        double delay = 0.0;

        explicit Reaction(std::vector<Species> reactants = {}, std::vector<Species> products = {}, const double rate = 0.0)
               : reactants(reactants), products(products), rate(rate) {}

        void print() const {
            myPrint(this->to_string());
        }

        // -> is dereference

        [[nodiscard]] std::string to_string() const {
            std::string out;
            for (size_t i = 0; i < reactants.size(); i++) {
                out += reactants[i].name;
                if (i < reactants.size() - 1) out += " + ";
            }
            out += " --(" + std::to_string(rate) + ")--> ";
            for (size_t i = 0; i < products.size(); i++) {
                out += products[i].name;
                if (i < products.size() - 1) out += " + ";
            }
            return out;
        }

        // We have a list of reactants.. If they meet (rate), then produce a result (products).

        //Uses Vessel quantities as state, can be modified to use external state
        void calculateDelay()
        {
            int sum = 1;
            for (const Species& sp : reactants) {
                sum *= sp.quantity;
            }

            delay = std::exp(rate * sum);
        }
    };


    std::ostream& operator<<(std::ostream& os, const Species& s) {
        os << "Species(name=" << s.name << ")";
        return os;
    }

    Reaction operator+(const Species& a, const Species& b) {
        return Reaction({ a, b});
    }

    // (A + B) + C → adds another Species to the list of reactants
    Reaction operator+(const Reaction& reaction, const Species& species) { // Er reaction pointer eller ikke?
        // reaction.reactants.push_back(species);
        // return reaction;

        std::vector<Species> new_reactants = reaction.reactants;
        new_reactants.push_back(species);
        return Reaction(new_reactants, reaction.products, reaction.rate);

    }

    // Reaction operator+(const Reaction& reaction, const Species& species) {
    //         std::vector<const Species&> new_reactants = reaction.reactants;
    //         new_reactants.push_back(species);
    //         return Reaction(new_reactants, reaction.products, reaction.rate);
    //     }



    // (A + B) >> 0.01 → sets the reaction rate
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




// struct ReactionBuilder {
//     std::vector<Species> reactants;
//     // std::vector<Species> products;
//     double rate;
//
//     // ReactionBuilder(Species s) : reactants{ s }, rate(0.0) {}
//     // ReactionBuilder(std::vector<Species> r) : reactants(r), rate(0.0) {}
// };
//
// // A + B → builds a ReactionBuilder from two Species
// ReactionBuilder operator+(Species a, Species b) {
//     return ReactionBuilder({ a, b});
// }
//
// // (A + B) + C → adds another Species to the list of reactants
// ReactionBuilder operator+(ReactionBuilder builder, Species s) {
//     builder.reactants.push_back(s);
//     return builder;
// }
//
// // (A + B) >> 0.01 → sets the reaction rate
// ReactionBuilder operator>>(ReactionBuilder builder, double rate) {
//     builder.rate = rate;
//     return builder;
// }
//
// //((A + B)) >> 0.01 >>= C → completes the reaction and creates a Reaction object
// ReactionBuilder operator>>=(ReactionBuilder builder, Species product) {
//     return Reaction{ builder.reactants, { product}, builder.rate };
// }
// Agent operator+(const Agent &a, const Agent &b) {
//     return a
// }



