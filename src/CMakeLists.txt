cmake_minimum_required(VERSION 3.12)

project(SRC)

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(BF_DEBUG)
ENDIF()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# SFML
#find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

# CInject
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cinject/include)

# ENTT
IF (MSVC)
	add_compile_definitions(NOMINMAX)
ENDIF()
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/entt/src)

# TermColor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/termcolor/include)

# ChaiScript
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/ChaiScript/include)

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
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/sol2/single/include)

# Box2D
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/Box2D)

# QuickJS++
# include_directories(${CMAKE_SOURCE_DIR}/thirdParties/quickjspp)

# YAML-CPP
include_directories(${CMAKE_SOURCE_DIR}/yaml-cpp/include)

# Common
include_directories(common)

# Math
include_directories(math)

# IO
include_directories(io)

include_directories(.)

# Common
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)

# IO
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/io)

# Math
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)

# BlackFox
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/blackfox)

# Game
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/game)

# Editor
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/editor)

add_dependencies(blackfox bfcommon bfio bfmath)
add_dependencies(game blackfox)
add_dependencies(editor blackfox)