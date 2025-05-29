#add_executable(sp_exam_project main.cpp)
#
#target_include_directories(sp_exam_project PRIVATE ../../lib/include)
#
#target_link_libraries(sp_exam_project PRIVATE stochastic_simulation)

add_executable(sp_exam_project main.cpp)

target_include_directories(sp_exam_project
        PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/include
#        ${CMAKE_SOURCE_DIR}/lib/src
        ${CMAKE_SOURCE_DIR}/lib/examples
)

target_link_libraries(sp_exam_project PRIVATE stochastic-simulation)