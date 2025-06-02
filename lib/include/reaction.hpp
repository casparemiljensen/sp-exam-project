#ifndef REACTION_HPP
#define REACTION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "species.hpp"

namespace StochasticSimulation {
    struct SimulationState;
    void myPrint(const std::string& s);



    struct Reaction {
        std::vector<Species> reactants;
        std::vector<Species> products;
        const double rate;
        double delay = 0.0;

        explicit Reaction(std::vector<Species> reactants = {}, std::vector<Species> products = {}, double rate = 0.0);
        void print() const;
        [[nodiscard]] std::string to_string() const;
        void calculateDelay(SimulationState&);
    };

    std::ostream& operator<<(std::ostream& os, const Species& s);
    Reaction operator+(const Species& a, const Species& b);
    Reaction operator+(const Reaction& reaction, const Species& species);
    Reaction operator>>(const Reaction& reaction, const double rate);
    Reaction operator>>(const Species& species, const double rate);
    Reaction operator>>(const Species& species, const int rate);
    Reaction operator>>=(const Reaction& reaction, const Species& product);
    Reaction operator>>=(const Reaction& reactionA, const Reaction& reactionB);

    std::string to_dot(const Reaction& reaction, const int index);
    std::string to_dot(const Species& species);
    std::string to_dot_network(const std::vector<Reaction>& reactions, const std::vector<Species>& species);
}

#endif //REACTION_HPP
