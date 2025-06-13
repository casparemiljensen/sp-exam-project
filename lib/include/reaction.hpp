#ifndef REACTION_HPP
#define REACTION_HPP

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

#include "species.hpp"

namespace StochasticSimulation {
    struct SimulationState;

    struct Reaction {
        std::vector<Species> reactants;
        std::vector<Species> products;
        const double rate;
        double delay = 0.0;

        virtual ~Reaction() = default;

        explicit Reaction(std::vector<Species> reactants = {}, std::vector<Species> products = {}, double rate = 0.0)
            : reactants(reactants), products(products), rate(rate) { }

        std::string createFingerprint() const {
            std::ostringstream oss;

            auto names = [](const std::vector<Species> vec) {
                std::vector<std::string> n;
                for (const auto &s: vec) n.push_back(s.name);
                std::sort(n.begin(), n.end());
                return n;
            };

            for (const auto &n: names(reactants)) oss << "R:" << n << ";";
            for (const auto &n: names(products)) oss << "P:" << n << ";";
            oss << "Rate:" << std::fixed << std::setprecision(6) << rate;

            return oss.str();
        }

        void print() const;

        [[nodiscard]] virtual std::string to_string(int padAmount = 7) const;

        static std::string center(const std::string& s, int width);

        void calculateDelay(SimulationState &);
    };

    // Requirement 1: The library should overload operators to support the reaction rule typesetting directly in C++ code.
    std::ostream &operator<<(std::ostream &os, const Species &s);

    Reaction operator+(const Species &a, const Species &b);

    bool operator==(const Species &a, const Species &b);

    Reaction operator+(const Reaction &reaction, const Species &species);

    Reaction operator>>(const Reaction &reaction, const double rate);

    Reaction operator>>(const Species &species, const double rate);

    Reaction operator>>(const Species &species, const int rate);

    Reaction operator>>=(const Reaction &reaction, const Species &product);

    Reaction operator>>=(const Reaction &reactionA, const Reaction &reactionB);

    // Requirement 2: Provide pretty-printing of the reaction network in: b) network graph.
    std::string to_dot(const Reaction &reaction, const int index);

    std::string to_dot(const Species &species);

    std::string to_dot_network(const std::vector<Reaction> &reactions, const std::vector<Species> &species);
}

#endif //REACTION_HPP
