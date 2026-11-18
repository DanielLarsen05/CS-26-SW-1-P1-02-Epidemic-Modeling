cmake_minimum_required(VERSION 4.0)

project(EpidemicModel)

add_executable(EpidemicModel)

add_library(simulation simulation.c matrix.c agents.c input_output.c)

target_sources(EpidemicModel PRIVATE main.c)

target_link_libraries(EpidemicModel simulation)
