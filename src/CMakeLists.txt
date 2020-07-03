cmake_minimum_required(VERSION 3.12)

project(SRC)

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

include_directories(.)

# BlackFox
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/blackfox)

# Game
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/game)

# Editor
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/editor)

# Test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

add_dependencies(game blackfox)
add_dependencies(editor blackfox)
add_dependencies(test blackfox)