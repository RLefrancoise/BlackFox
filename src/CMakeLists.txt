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
    ${Falcon_LIBRARIES} RTTR::Core_Lib ${SDL2_LIBRARIES}
)

target_compile_features(BlackFox PRIVATE cxx_std_17)