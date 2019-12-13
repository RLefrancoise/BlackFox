# Project
project(BlackFox)

# Build
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(BF_DEBUG)
ENDIF()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

# CInject
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cinject/include)

# ENTT
IF (MSVC)
	add_compile_definitions(NOMINMAX)
ENDIF()
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/entt/src)

# ImGui
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui)

# ENTT ImGui Entity Editor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui_entt_entity_editor)

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

# Files
file(
    GLOB_RECURSE
    SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "core/*.h"
    "core/*.cpp"
    "data/*.h"
    "data/*.cpp"
    "entities/*.h"
    "entities/*.cpp"
    "installers/*.h"
    "installers/*.cpp"
    "scripting/*.h"
    "scripting/*.cpp"
)

list(APPEND SOURCES main.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Scan folders macro
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(SOURCES_FOLDERS)

# Common
add_subdirectory(common)

# Math
add_subdirectory(math)

# IO
add_subdirectory(io)

# Executable
add_executable(
    BlackFox
    ${SOURCES}
)

# Add sources folders to target
target_include_directories(BlackFox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES_FOLDERS})

IF(WIN32)
    set(LIBRARIES sfml-graphics sfml-audio sfml-network bfcommon bfmath bfio fmt::fmt-header-only RTTR::Core libluadll)
ELSE()
    set(LIBRARIES sfml-graphics sfml-audio sfml-network bfcommon bfmath bfio fmt::fmt-header-only RTTR::Core libluadll dl pthread)
ENDIF()

target_link_libraries(
    BlackFox
	LINK_PUBLIC
	${LIBRARIES}
)

target_compile_features(BlackFox PRIVATE cxx_std_17)