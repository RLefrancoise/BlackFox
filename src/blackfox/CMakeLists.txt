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
    "core/*.h"
    "core/*.cpp"
    "data/*.h"
    "data/*.cpp"
    "entities/*.h"
    "entities/*.cpp"
    "installers/*.h"
    "installers/*.cpp"
    "scripting/*.h"
    "scripting/*.cpp"
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

# Executable
add_library(
    blackfox
    SHARED
    ${SOURCES}
)

# Add sources folders to target
target_include_directories(blackfox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES_FOLDERS})

IF(WIN32)
    set(LIBRARIES sfml-graphics sfml-audio sfml-network bfcommon bfmath bfio fmt::fmt-header-only RTTR::Core libluadll yaml-cpp)
ELSE()
    set(LIBRARIES sfml-graphics sfml-audio sfml-network bfcommon bfmath bfio fmt::fmt-header-only RTTR::Core libluadll yaml-cpp dl pthread)
ENDIF()

target_link_libraries(
    blackfox
	LINK_PUBLIC
	${LIBRARIES}
)

target_compile_features(blackfox PRIVATE cxx_std_17)