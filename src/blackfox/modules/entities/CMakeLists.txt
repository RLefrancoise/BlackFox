project(blackfox.entities)

# Files
file(
        GLOB_RECURSE
        SOURCES
        RELATIVE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "*.h"
        "*.cpp"
        "graphics/*.h"
        "graphics/*.cpp"
        "physics/*.h"
        "physics/*.cpp"
        "scripting/*.h"
        "scripting/*.cpp"
        "spatial/*.h"
        "spatial/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Library
IF(BLACKFOX_SHARED_LIB)
    add_library(
            blackfox.entities
            SHARED
            ${SOURCES}
    )
    target_compile_definitions(blackfox.entities PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
            blackfox.entities
            STATIC
            ${SOURCES}
    )
ENDIF()

target_include_directories(blackfox.entities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

IF(WIN32)
    set(LIBRARIES blackfox box2d)
ELSE()
    set(LIBRARIES blackfox box2d dl pthread)
ENDIF()

target_link_libraries(
        blackfox.entities
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(blackfox.entities PRIVATE cxx_std_17)