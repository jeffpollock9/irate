cmake_minimum_required(VERSION 3.0.0)

project(irate LANGUAGES CXX VERSION 0.0.1)

option(IRATE_TEST "Build tests" OFF)

message(STATUS "Configuring irate version: ${PROJECT_VERSION}")
message(STATUS "  Options:")
message(STATUS "   IRATE_TEST: ${IRATE_TEST}")

add_library(irate INTERFACE)

target_include_directories(irate INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(IRATE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

