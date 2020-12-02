cmake_minimum_required(VERSION 3.12)

project(SRC)

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    add_compile_definitions(BF_DEBUG)
ENDIF()

include_directories(.)

# BlackFox
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/blackfox)

# Game
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/game)

# Editor
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/editor)

# Test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

#add_dependencies(game blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics blackfox.scripting)
add_dependencies(editor blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics blackfox.scripting)
add_dependencies(test blackfox blackfox.input blackfox.entities blackfox.physics blackfox.graphics blackfox.scripting)