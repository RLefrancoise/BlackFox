cmake_minimum_required(VERSION 3.12)

project(Root)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

option(BLACKFOX_SHARED_LIB "Build BlackFox Shared lib? For now, only shared libs are supported, so it should be on" ON)

IF(NOT MSVC)
    add_compile_options(-Wa,-mbig-obj)
ENDIF()

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

# STD UUID
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/stduuid/include)
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/stduuid/catch)

# ThirdParties (ImGui, ...)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties)




IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    add_compile_definitions(BF_DEBUG)
ENDIF()

# CInject
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cinject/include)

# ENTT
IF (MSVC)
    add_compile_definitions(NOMINMAX)
ENDIF()
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/entt/src)

# TermColor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/termcolor/include)

# RTTR
find_package(RTTR CONFIG REQUIRED Core)

# Inih
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/inih)
if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
ENDIF()

# Lua
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/lua-5.3.5/src)

# Lua JIT
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties/luajit-2.0/src)

# Sol2
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/sol2/include)
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    add_compile_definitions(SOL_ALL_SAFETIES_ON)
ENDIF()
#include_directories(${CMAKE_SOURCE_DIR}/thirdParties/sol2/single/include)

# Box2D
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/Box2D)

# QuickJS++
# include_directories(${CMAKE_SOURCE_DIR}/thirdParties/quickjspp)

# YAML-CPP
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/yaml-cpp/include)

# YAML-Convert
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/yaml-convert)

# PhysFS
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/physfs-3.0.2/src)

# PhysFS++
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/physfs-cpp/include)

# Cereal
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cereal/include)






# SRC folder
add_subdirectory(src)

# Test Example folder
add_subdirectory(test_example)

IF(BLACKFOX_SHARED_LIB)
    target_compile_definitions(blackfox PUBLIC BLACKFOX_SHARED_LIB)
    #target_compile_definitions(game PUBLIC BLACKFOX_SHARED_LIB)
    target_compile_definitions(editor PUBLIC BLACKFOX_SHARED_LIB)
ENDIF()