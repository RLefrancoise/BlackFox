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

target_compile_features(imgui PUBLIC cxx_std_17)

# IMGUI SFML
add_subdirectory(imgui-sfml)

# IMGUI FileBrowser
file(
    GLOB
    IMGUI_FILEBROWSER_SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "ImGui-Addons/FileBrowser/ImGuiFileBrowser.h"
    "ImGui-Addons/FileBrowser/ImGuiFileBrowser.cpp"
)

add_library(imgui-filebrowser STATIC ${IMGUI_FILEBROWSER_SOURCES})

target_include_directories(
    imgui-filebrowser
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui-Addons/FileBrowser
)

target_link_libraries(
    imgui-filebrowser
    LINK_PUBLIC
    imgui
)

# IMGUI Color Text Edit
file(
    GLOB
    IMGUI_COLORTEXTEDIT_SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "ImGuiColorTextEdit/TextEditor.h"
    "ImGuiColorTextEdit/TextEditor.cpp"
)

add_library(imgui-colortextedit STATIC ${IMGUI_COLORTEXTEDIT_SOURCES})

target_include_directories(
    imgui-colortextedit
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui-sfml
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiColorTextEdit
)

target_link_libraries(
    imgui-colortextedit
    LINK_PUBLIC
    sfml-graphics
)

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

# YAML Convert
add_subdirectory(yaml-convert)