# Project
project(BlackFox)

# Build
#set(LIBRARY_OUTPUT_DIRECTORY bin/${CMAKE_BUILD_TYPE})

# Files
file(
    GLOB_RECURSE
    SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "common/*.h"
    "common/*.cpp"
    "core/*.h"
    "core/*.cpp"
    "installers/*.h"
    "installers/*.cpp"
    "resources/*.h"
    "resources/*.cpp"
    "math/*.h"
    "math/*.cpp"
    "utils/*.h"
    "utils/*.cpp"
)

#list(APPEND SOURCES main.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

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

# Library
IF(BLACKFOX_SHARED_LIB)
    add_library(
        blackfox
        SHARED
        ${SOURCES}
    )
    target_compile_definitions(blackfox PRIVATE BLACKFOX_SHARED_LIB_EXPORT)
ELSE()
    add_library(
        blackfox
        STATIC
        ${SOURCES}
    )
ENDIF()

# Add sources folders to target
target_include_directories(blackfox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES_FOLDERS})

IF(WIN32)
    set(LIBRARIES sfml-system sfml-graphics sfml-audio sfml-network fmt::fmt-header-only RTTR::Core libluadll yaml-cpp box2d physfs physfs++)
ELSE()
    set(LIBRARIES sfml-system sfml-graphics sfml-audio sfml-network fmt::fmt-header-only RTTR::Core liblua yaml-cpp box2d physfs physfs++ dl pthread)
ENDIF()

target_link_libraries(
    blackfox
	LINK_PUBLIC
	${LIBRARIES}
)

target_compile_features(blackfox PRIVATE cxx_std_17)

# Modules
add_subdirectory(modules)