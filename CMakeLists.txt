cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tamp_exercises LANGUAGES CXX)

add_compile_options("-Wall" "-Wextra" "-Wpedantic")
add_compile_options("-g" "-ggdb")

# Require C++14
set(CMAKE_CXX_STANDARD           14)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS         OFF)

# Library
add_subdirectory(lib)

# Tests
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
enable_testing()
add_subdirectory(tests)

# Exercises
add_subdirectory(c1/dining)

# vim: tabstop=4 shiftwidth=4 softtabstop=4 expandtab
