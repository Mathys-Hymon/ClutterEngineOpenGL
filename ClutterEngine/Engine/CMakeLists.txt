cmake_minimum_required(VERSION 3.16)

project(ClutterEngine)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions(CLUTTERENGINE_EXPORTS)

# Sources du moteur
file(GLOB_RECURSE CLUTTER_ENGINE_SRC
    "Application/*.cpp"
    "Core/*.cpp"
    "Graphics/*.cpp"
    "Input/*.cpp"
    "Physics/*.cpp"
    "Window/*.cpp"
    "Header/pch.cpp"
)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/Header/pch.cpp
    PROPERTIES LANGUAGE CXX
)

set(PCH_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Header/pch.h")
set(PCH_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Header/pch.cpp")

list(APPEND CLUTTER_ENGINE_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/include/glad/glad.c"
)

add_library(ClutterEngine SHARED ${CLUTTER_ENGINE_SRC})

target_include_directories(ClutterEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Application
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Physics
    ${CMAKE_CURRENT_SOURCE_DIR}/Window
    ${CMAKE_CURRENT_SOURCE_DIR}/Header
    ${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/include/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/include/FreeType
)


target_link_directories(ClutterEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/lib
)

target_link_libraries(ClutterEngine PRIVATE
    freetype
    glfw3
    opengl32
)

set_target_properties(ClutterEngine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
