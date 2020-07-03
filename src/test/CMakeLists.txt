project(test)

# Catch
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/Catch2/single_include)

# Files
file(
        GLOB_RECURSE
        SOURCES
        RELATIVE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "*.h"
        "*.cpp"
        "entities/*.h"
        "entities/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(test ${SOURCES})

IF(WIN32)
    set(LIBRARIES Catch2 sfml-system sfml-graphics sfml-audio sfml-network blackfox fmt::fmt-header-only RTTR::Core libluadll)
ELSE()
    set(LIBRARIES Catch2 sfml-system sfml-graphics sfml-audio sfml-network blackfox fmt::fmt-header-only RTTR::Core liblua dl pthread)
ENDIF()

target_link_libraries(
        test
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(test PRIVATE cxx_std_17)