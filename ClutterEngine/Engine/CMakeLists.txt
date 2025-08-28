cmake_minimum_required(VERSION 3.16)

project(ClutterEngine)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Définition pour l'export DLL
add_compile_definitions(CLUTTERENGINE_EXPORTS)

file(GLOB_RECURSE CLUTTER_ENGINE_SRC
    "Application/*.cpp"
    "Core/*.cpp"
    "Graphics/*.cpp"
    "Input/*.cpp"
    "Physics/*.cpp"
    "Window/*.cpp"
    "../Libraries/include/glad/glad.c"
    "Header/pch.cpp"
)


# Crée la DLL
add_library(ClutterEngine SHARED ${CLUTTER_ENGINE_SRC})

# Includes
target_include_directories(ClutterEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}        # racine Engine
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

# Bibliothèques
target_link_directories(ClutterEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/lib
)

target_link_libraries(ClutterEngine PRIVATE
    freetype
    glfw3
    opengl32
)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/Header/pch.cpp
    PROPERTIES LANGUAGE CXX
)


# Propriétés
set_target_properties(ClutterEngine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
