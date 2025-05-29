#ifndef EXPONENTIAL_DECAY_HPP
#define EXPONENTIAL_DECAY_HPP
#include "vessels.hpp"

namespace StochasticSimulation::Examples {
    Vessel exponential_decay(uint32_t q_a, uint32_t q_b, uint32_t q_c) {
        auto v = Vessel{"Exponential Decay"};

        constexpr auto rate = 0.001;
        const auto A = v.add("A", q_a);
        const auto B = v.add("B", q_b);
        const auto C = v.add("C", q_c);

        v.add((A + B) >> rate >>= B + C);
        return v;
    }
}

#endif //EXPONENTIAL_DECAY_HPP
