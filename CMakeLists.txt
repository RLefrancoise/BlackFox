cmake_minimum_required(VERSION 3.7)

project(Root)

# ThirdParties (ImGui, ...)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties)

# SRC folder
add_subdirectory(src)