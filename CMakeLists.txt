cmake_minimum_required(VERSION 3.7)

# Project
project(BlackFox)

# Build
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window network audio system main REQUIRED)

link_directories(${SFML_LIBRARY_DIRS})
include_directories(${SFML_INCLUDE_DIRS})

# Files
file(
    GLOB_RECURSE
    source_files
    src/*
)

# Executable
add_executable(
    BlackFox
    ${source_files}
)

target_link_libraries(
    BlackFox
    sfml-graphics sfml-window sfml-network sfml-audio sfml-system sfml-main
)

target_compile_features(BlackFox PRIVATE cxx_std_17)