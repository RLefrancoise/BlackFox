cmake_minimum_required(VERSION 3.7)

# Project
project(BlackFox)

# Build
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# CPP-SDL2
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties/cpp-sdl2/sources)

# Falcon
find_package(Falcon REQUIRED)

link_directories(${Falcon_LIBRARY_DIRS})
include_directories(${Falcon_INCLUDE_DIRS})

# RTTR
find_package(RTTR CONFIG REQUIRED Core)

# SRC folder
add_subdirectory(src)