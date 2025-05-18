#include <iostream>
#include "reaction.cpp" // Should be HPP!!!

int main() {
    std::cout << "Hello, World!" << std::endl;

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

    // // Test 3: Single species reacts to another
    // Reaction r3 = A >> 0.02 >>= B;
    // std::cout << "Reaction 3: ";
    // r3.print();  // Expected: A --(0.02)--> B

    // Test 4: Use temporary Species directly
    Reaction r4 = (Species("X") + Species("Y")) >> 0.1 >>= Species("Z");
    std::cout << "Reaction 4: ";
    r4.print();  // Expected: X + Y --(0.1)--> Z


    return 0;
}