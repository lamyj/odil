cmake_minimum_required(VERSION 2.8)
project("dcmtkpp")

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
