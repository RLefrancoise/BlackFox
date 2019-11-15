cmake_minimum_required(VERSION 3.7)

# Project
project(ThirdParties)

# ImGui
file(
    GLOB
    IMGUI_SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "imgui/*.h"
    "imgui/*.cpp"
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# fmt
add_subdirectory(fmt-6.0.0)