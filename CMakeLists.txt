cmake_minimum_required(VERSION 3.12)

project(Root)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# ThirdParties (ImGui, ...)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties)

# SRC folder
add_subdirectory(src)