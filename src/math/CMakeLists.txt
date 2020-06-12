project(bfmath)

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

IF(BLACKFOX_SHARED_LIB)
    add_library(bfmath SHARED ${SOURCES})
ELSE()
    add_library(bfmath STATIC ${SOURCES})
ENDIF()

set(LIBRARIES sfml-system fmt::fmt-header-only)

target_link_libraries(bfmath PUBLIC ${LIBRARIES})
target_compile_features(bfmath PUBLIC cxx_std_17)