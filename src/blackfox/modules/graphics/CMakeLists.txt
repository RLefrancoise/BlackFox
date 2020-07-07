project(blackfox.graphics)

# Files
file(
        GLOB_RECURSE
        SOURCES
        RELATIVE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "*.h"
        "*.cpp"
        "components/*.h"
        "components/*.cpp"
        "systems/*.h"
        "systems/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Library
IF(BLACKFOX_SHARED_LIB)
    add_library(
            blackfox.graphics
            SHARED
            ${SOURCES}
    )
    target_compile_definitions(blackfox.graphics PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
            blackfox.graphics
            STATIC
            ${SOURCES}
    )
ENDIF()

target_include_directories(blackfox.graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

IF(WIN32)
    set(LIBRARIES blackfox blackfox.entities blackfox.physics box2d)
ELSE()
    set(LIBRARIES blackfox blackfox.entities blackfox.physics box2d dl pthread)
ENDIF()

target_link_libraries(
        blackfox.graphics
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(blackfox.graphics PRIVATE cxx_std_17)