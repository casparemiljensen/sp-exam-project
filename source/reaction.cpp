#include <string>
#include <vector>
#include "reaction.hpp"
#include <sstream>
#include <iostream>
#include <set>

void myPrint(std::string s) {
    std::cout << s << std::endl;
}

struct Species {
    std::string name;
    int quantity; // How many units of this species exist

    // Constructor to initialize a Species with its name
    Species(std::string name, int quantity = 0) : name(std::move(name)), quantity(quantity) {}
};


struct Reaction { // Represents a reaction. E.g. A + C --(λ)--> B + C
    std::vector<Species*> reactants; // A, C (Input species)
    std::vector<Species*> products; // B, C (output species)
    double rate; //The rate λ describes the intrinsic probability of individuals meeting and reacting over one time unit.

    Reaction(std::vector<Species*> reactants = {}, std::vector<Species*> products = {}, double rate = 0.0)
           : reactants(std::move(reactants)), products(std::move(products)), rate(rate) {}

    void print() {
        myPrint(this->to_string());
    }
    // -> is dereference

    std::string to_string()
    {
        std::string out = "";
        for (size_t i = 0; i < reactants.size(); i++) {
            out += reactants[i]->name;
            if (i < reactants.size() - 1) out += " + ";
        }
        out += " --(" + std::to_string(rate) + ")--> ";
        for (size_t i = 0; i < products.size(); i++) {
            out += products[i]->name;
            if (i < products.size() - 1) out += " + ";
        }
        return out;
    }
    // We have a list of reactants.. If they meet (rate), then produce a result (products).
};


std::ostream& operator<<(std::ostream& os, const Species& s) {
    os << "Species(name=" << s.name << ")";
    return os;
}

Reaction operator+(Species& a, Species& b) {
    return Reaction({ &a, &b});
}

// (A + B) + C → adds another Species to the list of reactants
Reaction operator+(Reaction reaction, Species& s) { // Er reaction pointer eller ikke?
    reaction.reactants.push_back(&s);
    return reaction;
}

// (A + B) >> 0.01 → sets the reaction rate
Reaction operator>>(Reaction reaction, double rate) {
    reaction.rate = rate;
    return reaction;
}

//((A + B)) >> 0.01 >>= C → completes the reaction and creates a Reaction object
Reaction operator>>=(Reaction reaction, Species& product) {
    return Reaction{ reaction.reactants, { &product }, reaction.rate };
}


std::string to_dot(const Reaction& reaction, int index) {
    std::ostringstream out;
    std::string rname = "r" + std::to_string(index);
    out << "  " << rname << " [label=\"λ=" << reaction.rate << "\",shape=\"oval\",fillcolor=\"yellow\",style=\"filled\"];\n";
    for (const auto& reactant : reaction.reactants) {
        out << "  " << reactant->name << " -> " << rname << ";\n";
    }
    for (const auto& product : reaction.products) {
        out << "  " << rname << " -> " << product->name << ";\n";
    }
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



