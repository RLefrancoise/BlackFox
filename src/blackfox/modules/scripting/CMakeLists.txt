project(blackfox.scripting)

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
        "lua/*.h"
        "lua/*.cpp"
        "systems/*.h"
        "systems/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Library
IF(BLACKFOX_SHARED_LIB)
    add_library(
            blackfox.scripting
            SHARED
            ${SOURCES}
    )
    target_compile_definitions(blackfox.scripting PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
            blackfox.scripting
            STATIC
            ${SOURCES}
    )
ENDIF()

target_include_directories(blackfox.scripting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

IF(WIN32)
    set(LIBRARIES blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics box2d RTTR::Core libluadll)
ELSE()
    set(LIBRARIES blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics box2d RTTR::Core liblua dl pthread)
ENDIF()

target_link_libraries(
        blackfox.scripting
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(blackfox.scripting PRIVATE cxx_std_17)