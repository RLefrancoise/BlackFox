project(imgui-sfml)

add_compile_definitions(IMGUI_USER_CONFIG="imconfig-SFML.h")
#add_compile_definitions(IMGUI_SFML_SHARED_LIB)
#add_compile_definitions(IMGUI_SFML_EXPORTS)

add_library(imgui-sfml
    STATIC
    imgui-SFML_export.h
    imgui-SFML.cpp
    imgui-SFML.h)

target_include_directories(imgui-sfml INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../imgui"
)

target_link_libraries(imgui-sfml LINK_PUBLIC opengl32 glu32 imgui sfml-graphics sfml-system)

target_compile_features(imgui-sfml PUBLIC cxx_std_17)