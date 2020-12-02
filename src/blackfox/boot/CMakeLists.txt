project(blackfox.boot)

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
            blackfox.boot
            SHARED
            ${SOURCES}
    )
    target_compile_definitions(blackfox.boot PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
            blackfox.boot
            STATIC
            ${SOURCES}
    )
ENDIF()

target_include_directories(blackfox.boot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

IF(WIN32)
    set(LIBRARIES blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics blackfox.scripting)
ELSE()
    set(LIBRARIES blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics blackfox.scripting dl pthread)
ENDIF()

target_link_libraries(
        blackfox.boot
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(blackfox.boot PRIVATE cxx_std_17)