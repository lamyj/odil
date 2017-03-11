cmake_minimum_required(VERSION 2.8)

project("odil")
set(odil_MAJOR_VERSION 0)
set(odil_MINOR_VERSION 7)
set(odil_PATCH_VERSION 2)
set(odil_VERSION
    ${odil_MAJOR_VERSION}.${odil_MINOR_VERSION}.${odil_PATCH_VERSION})

option(BUILD_SHARED_LIBS "Build Odil with shared libraries." ON)
option(BUILD_EXAMPLES "Build the examples directory." ON)
option(BUILD_PYTHON_WRAPPERS "Build the Python Wrappers." ON)
option(BUILD_JAVASCRIPT_WRAPPERS "Build the Javascript Wrappers." OFF)

option(WITH_DCMTK "Build the DCMTK converter" ON)
option(
    USE_BUILTIN_DCMTK_GETSCU
    "Compile a locally packaged version of getscu for old DCMTK versions" ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
include(CTest)
include(cmake/functions.cmake)

# Add the C++0x or C++11 flag
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG(-std=c++11 COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG(-std=c++0x COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
    # We have to set _WIN32_WINNT for Asio
    if(${CMAKE_SYSTEM_VERSION} EQUAL 10) # Windows 10
        add_definitions(-D _WIN32_WINNT=0x0A00)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.3) # Windows 8.1
        add_definitions(-D _WIN32_WINNT=0x0603)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.2) # Windows 8
        add_definitions(-D _WIN32_WINNT=0x0602)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.1) # Windows 7
        add_definitions(-D _WIN32_WINNT=0x0601)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.0) # Windows Vista
        add_definitions(-D _WIN32_WINNT=0x0600)
    else() # Windows XP (5.1)
        add_definitions(-D _WIN32_WINNT=0x0501)
    endif()
endif()

add_subdirectory("src")
add_subdirectory("applications")

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

if(BUILD_TESTING)
    add_subdirectory("tests")
endif()

if(BUILD_PYTHON_WRAPPERS)
    add_subdirectory("wrappers/python")
endif()

if(BUILD_JAVASCRIPT_WRAPPERS)
    add_subdirectory("wrappers/js")
endif()

add_custom_target(
    CIIntegration ${CMAKE_COMMAND} -E echo "CI Integration"
    SOURCES appveyor.yml .gitlab-ci.yml .travis.yml)
set_target_properties(CIIntegration PROPERTIES FOLDER "Utils")

add_custom_target(
    Documentation ${CMAKE_COMMAND} -E echo "Documentation"
    SOURCES Doxyfile LICENSE.txt README.md)
set_target_properties(Documentation PROPERTIES FOLDER "Utils")

add_custom_target(
    Registry ${CMAKE_COMMAND} -E echo "Registry"
    SOURCES generate_registry registry.cpp.tmpl registry.h.tmpl)
set_target_properties(Registry PROPERTIES FOLDER "Utils")
