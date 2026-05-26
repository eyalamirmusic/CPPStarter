cmake_minimum_required(VERSION 3.21)
project(CPPStarter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

include(CPPStarterWarnings)

option(CPPSTARTER_BUILD_TESTS "Build CPPStarter tests" OFF)
option(CPPSTARTER_BUILD_APPS "Build CPPStarter apps" OFF)

add_subdirectory(Lib)

if (PROJECT_IS_TOP_LEVEL OR CPPSTARTER_BUILD_APPS)
    add_subdirectory(Apps)
endif ()

if (PROJECT_IS_TOP_LEVEL OR CPPSTARTER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif ()
