cmake_minimum_required(VERSION 3.0.0)

project(irate LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(IRATE_TEST "Build tests" OFF)
option(IRATE_BENCHMARK "Build benchmarks" OFF)

message(STATUS "Configuring irate version: ${PROJECT_VERSION}")
message(STATUS "  Options:")
message(STATUS "   IRATE_TEST: ${IRATE_TEST}")
message(STATUS "   IRATE_BENCHMARK: ${IRATE_BENCHMARK}")

add_library(irate INTERFACE)

target_include_directories(irate INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(irate INTERFACE cxx_std_17)

if(IRATE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

if(IRATE_BENCHMARK)
    add_subdirectory(benchmark)
endif()

set(CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(VERSION_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(PROJECT_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

set(NAMESPACE "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${VERSION_CONFIG}
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_file(${PROJECT_SOURCE_DIR}/cmake/config.cmake.in
    ${PROJECT_CONFIG} @ONLY)

install(TARGETS irate EXPORT ${TARGETS_EXPORT_NAME})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp")

install(FILES ${PROJECT_CONFIG} ${VERSION_CONFIG}
    DESTINATION ${CONFIG_INSTALL_DIR})

install(EXPORT ${TARGETS_EXPORT_NAME}
    NAMESPACE ${NAMESPACE}
    DESTINATION ${CONFIG_INSTALL_DIR})
