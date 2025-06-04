# sp-exam-project


## Requirements
Install **graphviz** https://graphviz.org/download/ & Setup path in environment variables
Install **qtChart**

To generate the network graph, run the following command:
```
cd /graphs
dot -Tpng network.dot -o network.png
```

SEIHR
susceptible-exposed-infected-hospitalized-removed


Species:
- A part of a chemical reaction
- Two species can react, and form a new species.


Vessel
- Holds the current state
- Knows the reaction rules
- Applies reactions
- Advances the clock
- Definition of the reaction network

State
- Snapshot of the system at one time

Simulator
- Owns or receives a Vessel
- Controls the simulation loop
- Picks which reaction to fire next (Gillespie algorithm)
- Advances time
- Logs SimulationStates
- Runs multiple simulations (parallel/serial)
- Writes output (CSV, console, whatever)


// -> is dereference



Notes
- Dont use auto for input types
- We cant have references in vectors
- Dereference: *Reaction or &Reaction
- uint32 is portable - _t is a naming style, avoid naming collision.
- No const in parameters of examples - We pass-by-value - const doest not change anything.
  - You're not modifying them anyway.
  - The compiler doesn’t care.
  - It doesn’t improve performance, safety, or clarity.
  - It clutters the signature.
- Req 7: Observer is not part of the library. The lib receives an observer, that is passed from the bin/src/main

Questions
- Why do we need inline keyword in the examples?
- What is constexpr
  - An expr evaluated by compiler at compile-time (Never run-time)
  - Not much that can run like this, but very performant.
- Brug kun target_include_directories(...) til headers
- Linking error: Due to include of reaction.cpp file in reaction.hpp.

TODO
- FIX Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)
- Investigate why mutable on line 16 in reaction.cpp works/fix!
- Find out if we need state
- Fix the usage of relative path -> should all be absoultes!
- Use correct naming conventions!
- Avoid copying (Don't create a bunch of unnecessary copies of objects etc.). 
- Const correctness. Try to use const as much as possible, but still think if it is reasonable to do.
- Pay attention to safety and performance when writing in C++ (should be on the top of our mind always).
- Find alternative to <generator> or create a custom generator header file to include since it doesnt work on windows)
- Comment where requirements is used, in code.
- Clean cmake files, lib/src

Bugs (Fixed)
- Segmentation Fault in vessels.hpp - returned Species& changed to Species