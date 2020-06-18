# Project
project(game)

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
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

# Executable
add_executable(
    game
    main.cpp
    BFBootstrap.cpp
    BFBootstrap.h
)

# Add sources folders to target
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES_FOLDERS})

IF(WIN32)
    set(LIBRARIES sfml-graphics sfml-audio sfml-network blackfox fmt::fmt-header-only RTTR::Core libluadll)
ELSE()
    set(LIBRARIES sfml-graphics sfml-audio sfml-network blackfox fmt::fmt-header-only RTTR::Core liblua dl pthread)
ENDIF()

target_link_libraries(
    game
	LINK_PUBLIC
	${LIBRARIES}
)

target_compile_features(game PRIVATE cxx_std_17)

# Set working directory to test, hardcoded here for now
IF(MSVC)
    set_property(TARGET game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_example")
ENDIF()