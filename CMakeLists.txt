cmake_minimum_required(VERSION 3.22)

set(EXECUTABLE_NAME LearnOpenGL)
project(${EXECUTABLE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 3.3 REQUIRED)

include_directories(include)
include_directories(glad/include)
set(SOURCES
	src/main.cpp
	glad/src/glad.c)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} glfw)