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

set(LIBRARIES fmt::fmt-header-only)

target_include_directories(bfcommon PUBLIC ${SOURCES_FOLDERS})
target_link_libraries(bfcommon PUBLIC ${LIBRARIES})
target_compile_features(bfcommon PUBLIC cxx_std_17)