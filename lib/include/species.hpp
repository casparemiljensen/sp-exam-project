
#ifndef SPECIES_HPP
#define SPECIES_HPP
#include <string>

namespace StochasticSimulation {
    struct Species {
        std::string name;
        mutable int quantity;

        explicit Species(std::string name, int quantity = 0);
        Species();
    };
}

#endif //SPECIES_HPP
