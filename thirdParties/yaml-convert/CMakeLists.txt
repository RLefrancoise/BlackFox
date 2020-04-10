project(yaml-convert)

# ImGui
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui)

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

add_library(yaml-convert STATIC ${SOURCES})

set(LIBRARIES yaml-cpp imgui)

target_link_libraries(yaml-convert LINK_PUBLIC ${LIBRARIES})
target_compile_features(yaml-convert PUBLIC cxx_std_17)