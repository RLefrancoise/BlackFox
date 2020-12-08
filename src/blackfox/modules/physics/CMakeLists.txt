project(blackfox.physics)

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
            blackfox.physics
            SHARED
            ${SOURCES}
    )
    target_compile_definitions(blackfox.physics PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
            blackfox.physics
            STATIC
            ${SOURCES}
    )
ENDIF()

target_include_directories(blackfox.physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

IF(WIN32)
    set(LIBRARIES blackfox blackfox.entities box2d RTTR::Core)
ELSE()
    set(LIBRARIES blackfox blackfox.entities box2d RTTR::Core dl pthread)
ENDIF()

target_link_libraries(
        blackfox.physics
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(blackfox.physics PRIVATE cxx_std_17)