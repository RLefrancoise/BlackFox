# Project
project(BlackFox)

# Build
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# SDL2
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdParties/cpp-sdl2/examples/cmake-modules/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# CPP-SDL2
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/cpp-sdl2/sources)

# ENTT
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/entt/src)

# ImGui
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui)

# ENTT ImGui Entity Editor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui_entt_entity_editor)

# Falcon
find_package(Falcon REQUIRED)
link_directories(${Falcon_LIBRARY_DIRS})
include_directories(${Falcon_INCLUDE_DIRS})

# RTTR
# find_package(RTTR CONFIG REQUIRED Core)

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

# Executable
add_executable(
    BlackFox
    ${SOURCES}
)

target_link_libraries(
    BlackFox
	LINK_PUBLIC
    ${Falcon_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY} # RTTR::Core_Lib
)

# target_include_directories(BlackFox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../thirdParties/imgui)

target_compile_features(BlackFox PRIVATE cxx_std_17)