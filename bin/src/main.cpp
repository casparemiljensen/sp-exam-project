#include <iostream>
#include <sstream>
#include <fstream>

#include "circadian_rythm.hpp"
#include "covid-19.hpp"
#include "exponential_decay.hpp"
#include "simulator.hpp"

using namespace StochasticSimulation;
using namespace StochasticSimulation::Examples;

int main() {

    // Species A("A");
    // Species B("B");
    // Species C("C");
    //
    // Reaction r = A + B >> 0.01 >>= C;
    //
    // r.print();

    Species A("A"), B("B"), C("C"), D("D");

    // Test 1: Basic reaction A + B -> C
    Reaction r1 = (A + B) >> 0.01 >>= C;
    std::cout << "Reaction 1: ";
    r1.print();  // Expected: A + B --(0.01)--> C


    // Test 2: Add three reactants: A + B + C -> D
    Reaction r2 = (A + B + C) >> 0.05 >>= D;
    std::cout << "Reaction 2: ";
    r2.print();  // Expected: A + B + C --(0.05)--> D

    // Test 3: Single species reacts to another
    Reaction r3 = A >> 0.02 >>= B;
    std::cout << "Reaction 3: ";
    r3.print();  // Expected: A --(0.02)--> B

    // Test 3.5: Single species reacts to another
    Reaction r4 = A + B >> 0.02 >>= B + C;
    std::cout << "Reaction 3.5: ";
    r4.print();  // Expected: A --(0.02)--> B

    // Test 4: Use temporary Species directly
    // Reaction r4 = (Species("X") + Species("Y")) >> 0.1 >>= Species("Z");
    // std::cout << "Reaction 4: ";
    // r4.print();  // Expected: X + Y --(0.1)--> Z


    std::vector vec = {r1, r2, r3, r4};
    std::vector vect = {A, B, C, D};


    Vessel circadian_rythm = circadian_rhythm();

    Vessel exponential_decay_a = exponential_decay(100,0,1);
    Vessel exponential_decay_b = exponential_decay(100,0,2);
    Vessel exponential_decay_c = exponential_decay(50,50,1);

    // std::string path = "/home/wired/dev/SP/sp-exam-project/";
    std::string path = "/Software/c++/sp-exam-project";
    std::ofstream out(path + "network.dot");
    out << to_dot_network(circadian_rythm.get_reactions(), circadian_rythm.get_species()) << std::endl;
    out << to_dot_network(vec, vect) << std::endl;
    out.close();

    Vessel covid = seihr(100);
    auto c = covid.createSimulationState();
    std::vector<SimulationState> trajectory;

    Simulator::simulate(1500, c, covid, trajectory);

    return 0;
}
