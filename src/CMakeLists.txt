# Project
project(BlackFox)

# Build
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# SDL2
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdParties/cpp-sdl2/examples/cmake-modules/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# CInject
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cinject/include)

# CPP-SDL2
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cpp-sdl2/sources)

# ENTT
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/entt/src)

# ImGui
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui)

# ENTT ImGui Entity Editor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui_entt_entity_editor)

# TermColor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/termcolor/include)

# ChaiScript
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/ChaiScript/include)

# Falcon
# find_package(Falcon REQUIRED)
# link_directories(${Falcon_LIBRARY_DIRS})
# include_directories(${Falcon_INCLUDE_DIRS})

# Files
file(
    GLOB_RECURSE
    SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
)

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

# Executable
add_executable(
    BlackFox
    ${SOURCES}
)

# Add sources folders to target
target_include_directories(BlackFox PUBLIC ${SOURCES_FOLDERS})

target_link_libraries(
    BlackFox
	LINK_PUBLIC
	${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY} fmt::fmt-header-only # ${Falcon_LIBRARIES}
)

# target_include_directories(BlackFox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../thirdParties/imgui)

target_compile_features(BlackFox PRIVATE cxx_std_17)