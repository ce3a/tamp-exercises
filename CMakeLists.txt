cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tamp_exercises LANGUAGES CXX)

add_compile_options("-Wall" "-Wextra" "-Wpedantic")
add_compile_options("-g" "-ggdb")

# Require C++14
set(CMAKE_CXX_STANDARD           14)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS         OFF)

add_subdirectory(c1/dining)

# vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
