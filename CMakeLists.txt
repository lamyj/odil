cmake_minimum_required(VERSION 2.8)

project("odil")
set(odil_MAJOR_VERSION 0)
set(odil_MINOR_VERSION 5)
set(odil_PATCH_VERSION 0)
set(odil_VERSION
    ${odil_MAJOR_VERSION}.${odil_MINOR_VERSION}.${odil_PATCH_VERSION})

option(BUILD_EXAMPLES "Build the examples directory." ON)
option(BUILD_WRAPPERS "Build the Python Wrappers." ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
include(CTest)

add_subdirectory("src")
add_subdirectory("applications")

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

if(BUILD_TESTING)
    add_subdirectory("tests")
endif()

if(BUILD_WRAPPERS)
    add_subdirectory("wrappers")
endif()

add_custom_target(
    CIIntegration ${CMAKE_COMMAND} -E echo "CI Integration"
    SOURCES appveyor.yml .travis.yml)

add_custom_target(
    Documentation ${CMAKE_COMMAND} -E echo "Documentation"
    SOURCES Doxyfile LICENSE.txt README.md)

add_custom_target(
    Registry ${CMAKE_COMMAND} -E echo "Registry"
    SOURCES generate_registry registry.cpp.tmpl registry.h.tmpl)
