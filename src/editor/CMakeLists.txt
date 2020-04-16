# Project
project(editor)

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(BF_DEBUG)
ENDIF()

# ImGui
include_directories(
    ${CMAKE_SOURCE_DIR}/thirdParties/imgui 
    ${CMAKE_SOURCE_DIR}/thirdParties/imgui/misc/cpp)

# ENTT ImGui Entity Editor
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui_entt_entity_editor)

# IMGUI SFML
add_compile_definitions(IMGUI_USER_CONFIG="imconfig-SFML.h")
#add_compile_definitions(IMGUI_SFML_SHARED_LIB)
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/imgui-sfml)

# IMGUI File browser
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/ImGui-Addons/FileBrowser)

# IMGUI Color Text Edit
include_directories(${CMAKE_SOURCE_DIR}/thirdParties/ImGuiColorTextEdit)

# Files
file(
    GLOB_RECURSE
    SOURCES
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
    "commands/*.h"
    "commands/*.cpp"
    "contexts/*.h"
    "contexts/*.cpp"
    "core/*.h"
    "core/*.cpp"
    "installers/*.h"
    "installers/*.cpp"
    "utils/*.h"
    "utils/*.cpp"
    "windows/*.h"
    "windows/*.cpp"
)

list(APPEND SOURCES main.cpp)
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
add_executable(
    editor
    ${SOURCES}
)

# Add sources folders to target
target_include_directories(editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES_FOLDERS})

IF(WIN32)
    set(LIBRARIES sfml-graphics sfml-audio sfml-network bfcommon bfmath bfio blackfox fmt::fmt-header-only RTTR::Core libluadll imgui-sfml imgui imgui-filebrowser imgui-colortextedit)
ELSE()
    set(LIBRARIES sfml-graphics sfml-audio sfml-network bfcommon bfmath bfio blackfox fmt::fmt-header-only RTTR::Core libluadll imgui-sfml imgui imgui-filebrowser imgui-colortextedit dl pthread)
ENDIF()

target_link_libraries(
    editor
	LINK_PUBLIC
	${LIBRARIES}
)

target_compile_features(editor PRIVATE cxx_std_17)