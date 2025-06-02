# sp-exam-project


## Requirements
Install **graphviz** https://graphviz.org/download/ & Setup path in environment variables


To generate the network graph, run the following command:
```
dot -Tpng network.dot -o network.png
```


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
- Brug kun target_include_directories(...) til headers
- Linking error: Due to include of reaction.cpp file in reaction.hpp.

TODO
- FIX Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)
- Investigate why mutable on line 16 in reaction.cpp works/fix!
- Find out if we need state
- 