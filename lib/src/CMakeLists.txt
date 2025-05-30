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
        ../../test/SymbolTableTests.cpp
        ../src/trajectory_chart_widget.cpp
        ../include/trajectory_chart_widget.hpp
        charter.cpp
        ../include/charter.hpp
        ../include/multithreading.hpp
        multithreading.cpp
        ../examples/mutli_threading.cpp # This is required for QT6 for some reason
)

# Sørg for at dit include virker
target_include_directories(stochastic-simulation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../examples
)

find_package(Qt6 COMPONENTS Core Gui Widgets Charts REQUIRED)

target_link_libraries(stochastic-simulation
        PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts
)


#find_package(doctest )


