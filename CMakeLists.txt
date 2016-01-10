cmake_minimum_required(VERSION 2.8)

project("dcmtkpp")
set(dcmtkpp_MAJOR_VERSION 0)
set(dcmtkpp_MINOR_VERSION 4)
set(dcmtkpp_PATCH_VERSION 0)
set(dcmtkpp_VERSION 
    ${dcmtkpp_MAJOR_VERSION}.${dcmtkpp_MINOR_VERSION}.${dcmtkpp_PATCH_VERSION})

option(BUILD_EXAMPLES "Build the examples directory." ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
include(CTest)

add_subdirectory("src")

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

if(BUILD_TESTING)
    add_subdirectory("tests")
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
