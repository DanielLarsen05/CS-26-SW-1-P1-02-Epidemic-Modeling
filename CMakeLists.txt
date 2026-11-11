cmake_minimum_required(VERSION 4.0)

project(EpidemicModel)

add_executable(EpidemicModel)

add_library(simulation setup_simulation.c matrix.c)

target_sources(EpidemicModel PRIVATE pandemic.c)

target_link_libraries(EpidemicModel simulation)
