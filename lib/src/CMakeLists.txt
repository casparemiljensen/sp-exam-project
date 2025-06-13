set(CMAKE_AUTOMOC ON) # enables Qt's MOC auto-processing
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Build the core library
add_library(stochastic-simulation STATIC
        simulator.cpp
        reaction.cpp
        state.cpp
        charter.cpp
        ../examples/multi_threading.cpp
        ../examples/circadian_rhythm.cpp
        ../examples/covid-19.cpp
        ../examples/exponential_decay.cpp
        ../src/trajectory_chart_widget.cpp
        ../include/trajectory_chart_widget.hpp
        ../include/charter.hpp
        ../include/multithreading.hpp
        ../include/debug_print.hpp
        ../../bin/src/utils.hpp
        ../examples/circadian_rhythm.hpp
)


target_include_directories(stochastic-simulation
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../examples
)

find_package(Qt6 COMPONENTS Core Gui Widgets Charts REQUIRED)

target_link_libraries(stochastic-simulation
        PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts
)
