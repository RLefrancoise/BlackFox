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
    "imgui/misc/cpp/*.h"
    "imgui/misc/cpp/*.cpp"
)

add_compile_definitions(IMGUI_USER_CONFIG="imconfig-SFML.h")

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(
    imgui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui-sfml)

target_link_libraries(
    imgui
    LINK_PUBLIC
    sfml-graphics)

# IMGUI SFML
add_subdirectory(imgui-sfml)

# fmt
add_subdirectory(fmt-6.0.0)

# SDL gfx
#add_subdirectory(SDL2_gfx_1.0.4)

# Lua
add_subdirectory(lua-5.3.5)

# Lua JIT
# add_subdirectory(luajit)

# Box2D
add_subdirectory(Box2D)

# QuickJS++
# add_subdirectory(quickjspp)

# YAML CPP
add_subdirectory(yaml-cpp)