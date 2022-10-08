cmake_minimum_required(VERSION 3.22)

set(EXECUTABLE_NAME LearnOpenGL)
project(${EXECUTABLE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Adding GLFW and Assimp to project
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(assimp)

# Include directories
include_directories(include)
include_directories(glad/include)
include_directories(stb_image)
include_directories(assimp/include)

# Sources and creating the executable
set(SOURCES
        glad/src/glad.c
        stb_image/stb_image.c
        src/main.cpp
        src/Shader.cpp
        src/Camera.cpp
        src/Mesh.cpp src/Model.cpp include/Model.h)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Linking GLFW and Assimp libraries
target_link_libraries(${EXECUTABLE_NAME} glfw)
target_link_libraries(${EXECUTABLE_NAME} assimp)
