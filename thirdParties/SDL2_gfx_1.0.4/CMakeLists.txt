project(sdl2gfx)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(
        GLOB
        SDL2_GFX_SOURCES
        RELATIVE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "*.h"
        "*.c"
)

add_library(sdl2gfx STATIC ${SDL2_GFX_SOURCES})

target_link_libraries(
        sdl2gfx
        LINK_PRIVATE
        ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY})