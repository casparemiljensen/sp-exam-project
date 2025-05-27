#include <string>
#include <vector>
#include "reaction.hpp"

#include <iostream>

struct Species {
    std::string name;
    int quantity; // How many units of this species exist

    // Constructor to initialize a Species with its name
    Species(std::string name, int quantity = 0) : name(std::move(name)), quantity(quantity) {}
};


struct Reaction { // Represents a reaction. E.g. A + C --(λ)--> B + C
    std::vector<Species> reactants; // A, C (Input species)
    std::vector<Species> products; // B, C (output species)
    double rate; //The rate λ describes the intrinsic probability of individuals meeting and reacting over one time unit.

    // Reaction(std::vector<Species*> reactants = {}, std::vector<Species*> products = {}, double rate = 0.0)
    //         : reactants(std::move(reactants)), products(std::move(products)), rate(rate) {}

    void print() {
        for (size_t i = 0; i < reactants.size(); ++i) {
            std::cout << reactants[i].name;
            if (i < reactants.size() - 1) std::cout << " + ";
        }
        std::cout << " --(" << rate << ")--> ";
        for (size_t i = 0; i < products.size(); ++i) {
            std::cout << products[i].name;
            if (i < products.size() - 1) std::cout << " + ";
        }
        std::cout << "\n";
    }
    // We have a list of reactants.. If they meet (rate), then produce a result (products).
};

Reaction operator+(Species a, Species b) {
    return Reaction({ a, b});
}

// (A + B) + C → adds another Species to the list of reactants
Reaction operator+(Reaction builder, Species s) {
    builder.reactants.push_back(s);
    return builder;
}

// (A + B) >> 0.01 → sets the reaction rate
Reaction operator>>(Reaction builder, double rate) {
    builder.rate = rate;
    return builder;
}

//((A + B)) >> 0.01 >>= C → completes the reaction and creates a Reaction object
Reaction operator>>=(Reaction builder, Species product) {
    return Reaction{ builder.reactants, { product}, builder.rate };
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



