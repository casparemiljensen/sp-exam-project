set(CMAKE_AUTOMOC ON)
find_package(Qt6 COMPONENTS Core Gui Widgets Charts REQUIRED)

add_executable(sp_exam_project main.cpp)

target_include_directories(sp_exam_project
        PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/include
        ${CMAKE_SOURCE_DIR}/lib/examples
)

find_package(Qt6 COMPONENTS Core Gui Widgets Charts REQUIRED)

target_link_libraries(sp_exam_project
        PRIVATE
        stochastic-simulation
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
        benchmark
)

target_link_libraries(stochastic-simulation
        PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts
)

target_compile_features(sp_exam_project PRIVATE cxx_std_20)