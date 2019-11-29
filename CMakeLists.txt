cmake_minimum_required(VERSION 3.12)

project(Root)

# ThirdParties (ImGui, ...)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties)

# SRC folder
add_subdirectory(src)