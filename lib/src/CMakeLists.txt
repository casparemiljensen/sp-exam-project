# Build the core library
add_library(stochastic-simulation STATIC
        simulator.cpp
        reaction.cpp
        state.cpp
        observer.cpp
        random.cpp
        agent.cpp
        ../examples/circadian_rythm.cpp
        ../examples/covid-19.cpp
        ../examples/exponential_decay.cpp
)

# Sørg for at dit include virker
target_include_directories(stochastic-simulation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../examples
)




