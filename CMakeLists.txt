cmake_minimum_required(VERSION 3.12)

project(Root)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

option(BLACKFOX_SHARED_LIB "Build BlackFox Shared lib? For now, only shared libs are supported, so it should be on" ON)

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

# STD UUID
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/stduuid/include)
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/stduuid/catch)

# ThirdParties (ImGui, ...)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties)

# SRC folder
add_subdirectory(src)

IF(BLACKFOX_SHARED_LIB)
    target_compile_definitions(blackfox PUBLIC BLACKFOX_SHARED_LIB)
    target_compile_definitions(game PUBLIC BLACKFOX_SHARED_LIB)
    target_compile_definitions(editor PUBLIC BLACKFOX_SHARED_LIB)
ENDIF()