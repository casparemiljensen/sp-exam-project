#ifndef VESSELS_HPP
#define VESSELS_HPP
#include <string>
#include <utility>

#include "symbol_table.hpp"
#include "../source/reaction.cpp"
// Todo Move implementation to cpp
template<typename Value>
class Vessel {
    SymbolTable<std::string, Value> species;
    std::vector<Reaction> reactions;
    std::string name;
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
        return _env;
    }

    std::vector<Reaction>& get_reactions() {
        return reactions;
    }

    const std::vector<Species>& get_species() {
        return species.getValues();
    }
};


Vessel<Species> circadian_rhythm()
{
    constexpr auto alphaA = 50;
    constexpr auto alpha_A = 500;
    constexpr auto alphaR = 0.01;
    constexpr auto alpha_R = 50;
    constexpr auto betaA = 50;
    constexpr auto betaR = 5;
    constexpr auto gammaA = 1;
    constexpr auto gammaR = 1;
    constexpr auto gammaC = 2;
    constexpr auto deltaA = 1;
    constexpr auto deltaR = 0.2;
    constexpr auto deltaMA = 10;
    constexpr auto deltaMR = 0.5;
    constexpr auto thetaA = 50;
    constexpr auto thetaR = 100;
    auto v = Vessel<Species>{"Circadian Rhythm"};
    const auto env = v.environment();
    const auto DA = v.add("DA", 1);
    const auto D_A = v.add("D_A", 0);
    const auto DR = v.add("DR", 1);
    const auto D_R = v.add("D_R", 0);
    const auto MA = v.add("MA", 0);
    const auto MR = v.add("MR", 0);
    const auto A = v.add("A", 0);
    const auto R = v.add("R", 0);
    const auto C = v.add("C", 0);
    v.add((A + DA) >> gammaA >>= D_A);
    v.add(D_A >> thetaA >>= DA + A);
    v.add((A + DR) >> gammaR >>= D_R);
    v.add(D_R >> thetaR >>= DR + A);
    v.add(D_A >> alpha_A >>= MA + D_A);
    v.add(DA >> alphaA >>= MA + DA);
    v.add(D_R >> alpha_R >>= MR + D_R);
    v.add(DR >> alphaR >>= MR + DR);
    v.add(MA >> betaA >>= MA + A);
    v.add(MR >> betaR >>= MR + R);
    v.add((A + R) >> gammaC >>= C);
    v.add(C >> deltaA >>= R);
    v.add(A >> deltaA >>= env);
    v.add(R >> deltaR >>= env);
    v.add(MA >> deltaMA >>= env);
    v.add(MR >> deltaMR >>= env);
    return v;
}

Vessel<Species> seihr(uint32_t N)
{
    auto v = Vessel<Species>{"COVID19 SEIHR: " + std::to_string(N)};
    const auto eps = 0.0009; // initial fraction of infectious
    const auto I0 = size_t(std::round(eps * N)); // initial infectious
    const auto E0 = size_t(std::round(eps * N * 15)); // initial exposed
    const auto S0 = N - I0 - E0; // initial susceptible
    const auto R0 = 2.4; // initial basic reproductive number
    const auto alpha = 1.0 / 5.1; // incubation rate (E -> I) ~5.1 days
    const auto gamma = 1.0 / 3.1; // recovery rate (I -> R) ~3.1 days
    const auto beta = R0 * gamma; // infection/generation rate (S+I -> E+I)
    const auto P_H = 0.9e-3; // probability of hospitalization
    const auto kappa = gamma * P_H * (1.0 - P_H); // hospitalization rate (I -> H)
    const auto tau = 1.0 / 10.12; // removal rate in hospital (H -> R) ⤦
    const auto S = v.add("S", S0); // susceptible
    const auto E = v.add("E", E0); // exposed
    const auto I = v.add("I", I0); // infectious
    const auto H = v.add("H", 0); // hospitalized
    const auto R = v.add("R", 0); // removed/immune (recovered + dead)
    v.add((S + I) >> beta / N >>= E + I); // susceptible becomes exposed by infectious
    v.add(E >> alpha >>= I); // exposed becomes infectious
    v.add(I >> gamma >>= R); // infectious becomes removed
    v.add(I >> kappa >>= H); // infectious becomes hospitalized
    v.add(H >> tau >>= R); // hospitalized becomes removed
    return v;
}

#endif // VESSELS_HPP
