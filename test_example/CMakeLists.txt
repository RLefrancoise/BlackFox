# Project
project(TestExample)

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    add_compile_definitions(BF_DEBUG)
ENDIF()

# Scan folders macro
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(SOURCES_FOLDERS)

# Files
file(
        GLOB_RECURSE
        SOURCES
        RELATIVE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "src/*.h"
        "src/*.cpp"
        "src/*.inl"
)

list(APPEND SOURCES src/main.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Executable
add_executable(
        TestExample
        ${SOURCES}
)

# Add sources folders to target
target_include_directories(TestExample PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES_FOLDERS})

IF(WIN32)
    set(
            LIBRARIES
            sfml-graphics
            sfml-audio
            sfml-network
            blackfox
            blackfox.input
            blackfox.entities
            blackfox.physics
            blackfox.graphics
            blackfox.scripting
            fmt::fmt-header-only
            RTTR::Core
            libluadll)
ELSE()
    set(
            LIBRARIES
            sfml-graphics
            sfml-audio
            sfml-network
            blackfox
            blackfox.input
            blackfox.entities
            blackfox.physics
            blackfox.graphics
            blackfox.scripting
            fmt::fmt-header-only
            RTTR::Core
            liblua
            dl
            pthread)
ENDIF()

target_link_libraries(
        TestExample
        LINK_PUBLIC
        ${LIBRARIES}
)

target_compile_features(TestExample PRIVATE cxx_std_17)

# Set working directory to test, hardcoded here for now
IF(MSVC)
    set_property(TARGET TestExample PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_example")
ENDIF()

IF(BLACKFOX_SHARED_LIB)
    target_compile_definitions(TestExample PUBLIC BLACKFOX_SHARED_LIB)
ENDIF()

add_dependencies(TestExample blackfox blackfox.boot blackfox.input blackfox.entities blackfox.physics blackfox.graphics blackfox.scripting)