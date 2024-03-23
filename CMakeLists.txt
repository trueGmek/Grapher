cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# CONFIGURE VCPKG
set(VCPKG_TARGET_TRIPLET x64-linux)
include(~/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

# FIND PACKAGES
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# CONFIGURE RENDERER LIBRARY
set(RENDERER_SOURCES
    src/renderer/shader.cpp
    src/renderer/shader.h
    src/renderer/renderer.h
    src/renderer/renderer.cpp
    src/renderer/GUI/GUI.cpp
    src/renderer/GUI/GUI.h
    src/renderer/primitives/primitive.h
    src/renderer/primitives/triangle.cpp
    src/renderer/primitives/triangle.h
    src/renderer/primitives/square.h
    src/renderer/primitives/square.cpp
    src/renderer/primitives/point.h
    src/renderer/primitives/point.cpp
)

add_library(renderer ${RENDERER_SOURCES})

target_include_directories(
  renderer PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/renderer>)

target_link_libraries(renderer PRIVATE glad::glad)
target_link_libraries(renderer PRIVATE glm::glm)
target_link_libraries(renderer PRIVATE imgui::imgui)

# CONFIGURE PORJECT
project(
  Grapher
  VERSION 1.0
  DESCRIPTION "Grapher"
  LANGUAGES CXX)

set(PROJECT_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)
