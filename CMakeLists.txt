cmake_minimum_required(VERSION 2.6)

project(markov C)
enable_testing()

SET(CMAKE_C_FLAGS_PROFILING "-pg" CACHE STRING "Flags for profiling builds")

add_subdirectory(src)
add_subdirectory(test)
