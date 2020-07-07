project(blackfox.input)

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

# Library
IF(BLACKFOX_SHARED_LIB)
    add_library(
            blackfox.input
            SHARED
            ${SOURCES}
    )
    target_compile_definitions(blackfox.input PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
            blackfox.input
            STATIC
            ${SOURCES}
    )
ENDIF()

target_include_directories(blackfox.input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

IF(WIN32)
    set(LIBRARIES blackfox sfml-system sfml-window)
ELSE()
    set(LIBRARIES blackfox sfml-system sfml-window dl pthread)
ENDIF()

target_link_libraries(
        blackfox.input
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(blackfox.input PRIVATE cxx_std_17)