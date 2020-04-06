project(bfio)

if(MSVC)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
ENDIF()

# TermColor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/termcolor/include)

# Inih
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/inih)
if(MSVC)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
ENDIF()

# Lua
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/lua-5.3.5/src)

# Lua JIT
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParties/luajit-2.0/src)

# Sol2
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/sol2/single/include)

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

set(LIBRARIES bfcommon libluadll)

target_include_directories(
        bfio
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src/common
)

target_link_libraries(bfio LINK_PUBLIC ${LIBRARIES})
target_compile_features(bfio PUBLIC cxx_std_17)