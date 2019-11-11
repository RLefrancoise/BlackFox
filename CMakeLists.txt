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

# Falcon
find_package(Falcon REQUIRED)

link_directories(${Falcon_LIBRARY_DIRS})
include_directories(${Falcon_INCLUDE_DIRS})

# RTTR
find_package(RTTR CONFIG REQUIRED Core)

# SRC folder
add_subdirectory(src)