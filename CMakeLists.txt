cmake_minimum_required(VERSION 2.8)

project("odil")
set(odil_MAJOR_VERSION 0)
set(odil_MINOR_VERSION 5)
set(odil_PATCH_VERSION 0)
set(odil_VERSION
    ${odil_MAJOR_VERSION}.${odil_MINOR_VERSION}.${odil_PATCH_VERSION})

option(BUILD_SHARED_LIBS "Build Odil with shared libraries." ON)
option(BUILD_EXAMPLES "Build the examples directory." ON)
option(BUILD_WRAPPERS "Build the Python Wrappers." ON)

option(WITH_DCMTK "Build the DCMTK converter" ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
include(CTest)
include(cmake/functions.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
    # Trying the automatic creation of .def files by CMake
    if(${BUILD_SHARED_LIBS})
        set(WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    endif()

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

if(BUILD_WRAPPERS)
    add_subdirectory("wrappers")
endif()

add_custom_target(
    CIIntegration ${CMAKE_COMMAND} -E echo "CI Integration"
    SOURCES appveyor.yml .travis.yml)
set_target_properties(CIIntegration PROPERTIES FOLDER "Utils")

add_custom_target(
    Documentation ${CMAKE_COMMAND} -E echo "Documentation"
    SOURCES Doxyfile LICENSE.txt README.md)
set_target_properties(Documentation PROPERTIES FOLDER "Utils")

add_custom_target(
    Registry ${CMAKE_COMMAND} -E echo "Registry"
    SOURCES generate_registry registry.cpp.tmpl registry.h.tmpl)
set_target_properties(Registry PROPERTIES FOLDER "Utils")
