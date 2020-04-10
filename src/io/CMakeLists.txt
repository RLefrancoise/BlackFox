project(bfio)

if(MSVC)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
ENDIF()

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

add_library(bfio STATIC ${SOURCES})

set(LIBRARIES bfcommon libluadll yaml-cpp)

target_include_directories(
        bfio
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src/common
)

target_link_libraries(bfio LINK_PUBLIC ${LIBRARIES})
target_compile_features(bfio PUBLIC cxx_std_17)