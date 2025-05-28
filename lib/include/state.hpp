#ifndef STATE_HPP
#define STATE_HPP
#include <unordered_map>
#include <string>

struct SimulationState {
    double time;
    std::unordered_map<std::string, int> species;
};

#endif //STATE_HPP



// Example

// SimulationState {
//     .time = 12.5,
//     .species = {
//         {"S", 50},
//         {"I", 30},
//         {"R", 20}
//     }
// }