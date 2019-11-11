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

# Executable
add_executable(
    BlackFox
    ${SOURCES}
)

target_link_libraries(
    BlackFox
    sfml-graphics sfml-window sfml-network sfml-audio sfml-system sfml-main ${Falcon_LIBRARIES} RTTR::Core_Lib
)

target_compile_features(BlackFox PRIVATE cxx_std_17)