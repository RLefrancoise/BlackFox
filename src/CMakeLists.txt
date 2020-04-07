cmake_minimum_required(VERSION 3.12)

project(SRC)

# Common
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)

# IO
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/io)

# Math
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)

# BlackFox
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/blackfox)

# Game
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/game)

# Editor
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/editor)