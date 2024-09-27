cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# CONFIGURE VCPKG
set(VCPKG_TARGET_TRIPLET x64-linux)
include(~/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

# FIND PACKAGES
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# UTILS
set(UTILS_NAME utils)
set(UTILS_SOURCES #
    src/utils/constants.h #
    src/parser/parser.h #
    src/parser/parser.cpp)

add_library(${UTILS_NAME} ${UTILS_SOURCES})

target_include_directories(
  ${UTILS_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/utils>)

target_link_libraries(${UTILS_NAME} PRIVATE glm::glm)

# PARSER
set(PARSER_LIB_NAME parser)
set(PARSER_LIB_SOURCES #
    src/parser/parser.h #
    src/parser/parser.cpp)

add_library(${PARSER_LIB_NAME} ${PARSER_LIB_SOURCES})

# CONFIGURE RENDERER LIBRARY

set(RENDERER_NAME renderer)
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
    src/renderer/primitives/line.h
    src/renderer/primitives/line.cpp
    src/renderer/graph/graph.cpp
    src/renderer/graph/graph.h
    src/renderer/camera/camera.h
    src/renderer/camera/camera.cpp
    src/renderer/transform.h
    src/renderer/sceneProvider.h
    src/renderer/GUI/graphView.h
    src/renderer/GUI/graphView.cpp
    src/renderer/GUI/equation/equationView.h
    src/renderer/GUI/equation/equationView.cpp
    src/renderer/input.h)

add_library(${RENDERER_NAME} ${RENDERER_SOURCES})

target_include_directories(
  ${RENDERER_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/renderer>)

target_link_libraries(${RENDERER_NAME} PRIVATE utils)
target_link_libraries(${RENDERER_NAME} PRIVATE glad::glad)
target_link_libraries(${RENDERER_NAME} PRIVATE glm::glm)
target_link_libraries(${RENDERER_NAME} PRIVATE imgui::imgui)

# CONFIGURE PORJECT
project(
  grapher
  VERSION 1.0
  DESCRIPTION "Grapher"
  LANGUAGES CXX)

set(PROJECT_FILES
    src/main.cpp #
    src/cameraController/cameraController.h
    src/cameraController/cameraController.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

# GTEST
enable_testing()
find_package(GTest CONFIG REQUIRED)

set(TESTS_LIB_NAME grapher_tests)

add_executable(${TESTS_LIB_NAME} tests/hello_test.cpp)

target_link_libraries(${TESTS_LIB_NAME} PRIVATE ${PARSER_LIB_NAME})
target_link_libraries(${TESTS_LIB_NAME} PRIVATE GTest::gtest GTest::gtest_main
                                                GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${TESTS_LIB_NAME})
