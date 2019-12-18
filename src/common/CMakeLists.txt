project(bfcommon)

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

add_library(bfcommon STATIC ${SOURCES})

set(LIBRARIES sfml-graphics fmt::fmt-header-only)

target_link_libraries(bfcommon LINK_PUBLIC ${LIBRARIES})
target_compile_features(bfcommon PUBLIC cxx_std_17)