# Build the core library
add_library(stochastic-simulation
        simulator.cpp
        reaction.cpp
        state.cpp
        observer.cpp
        random.cpp
        agent.cpp
)

#include_directories will tell to the compiler where to look for the header files, in this case, the header files for the boost library.
#
#target_link_libraries will tell to the linker which libraries you want to link against your executable.
#
#While headers will provide (most of the time) just the interface to access the library, the library itself is precompiled and linked to your application.


## Make sure it can see the headers from include/
target_include_directories(stochastic-simulation
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)



