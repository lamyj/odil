cmake_minimum_required(VERSION 3.5)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
cmake_policy(SET CMP0074 NEW)

project("Odil" VERSION 0.12.0)

option(BUILD_SHARED_LIBS "Build Odil with shared libraries." ON)
option(BUILD_EXAMPLES "Build the examples directory." ON)
option(BUILD_PYTHON_WRAPPERS "Build the Python Wrappers." ON)
option(BUILD_JAVASCRIPT_WRAPPERS "Build the Javascript Wrappers." OFF)

option(WITH_DCMTK "Build the DCMTK converter" ON)
option(
    USE_BUILTIN_DCMTK_GETSCU
    "Compile a locally packaged version of getscu for old DCMTK versions" ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
set(CMAKE_INSTALL_MESSAGE LAZY)

include(CTest)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    
    # Starting with Visual Studio 2015 / VC 14 / MSVC 19.00, snprintf is present
    if(${MSVC_VERSION} GREATER_EQUAL "1900")
        add_definitions(-D HAVE_SNPRINTF)
    endif()
endif()

add_subdirectory("src")

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

if(BUILD_TESTING)
    add_subdirectory("tests")
endif()

if(BUILD_PYTHON_WRAPPERS)
    add_subdirectory("wrappers/python")
    add_subdirectory("applications")
endif()

if(BUILD_JAVASCRIPT_WRAPPERS)
    add_subdirectory("wrappers/js")
endif()

file(GLOB_RECURSE ci_resources .ci/*)
add_custom_target(
    CIIntegration ${CMAKE_COMMAND} -E echo "CI Integration"
    SOURCES appveyor.yml .travis.yml ${ci_resources})
set_target_properties(CIIntegration PROPERTIES FOLDER "Utils")

file(GLOB_RECURSE documentation documentation/*)
add_custom_target(
    Documentation ${CMAKE_COMMAND} -E echo "Documentation"
    SOURCES LICENSE.txt README.md ${documentation})
set_target_properties(Documentation PROPERTIES FOLDER "Utils")

file(GLOB_RECURSE registry_templates registry*.tmpl)
add_custom_target(
    Registry ${CMAKE_COMMAND} -E echo "Registry"
    SOURCES generate_registry ${registry_templates})
set_target_properties(Registry PROPERTIES FOLDER "Utils")

set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/lib")
if(WIN32 AND NOT CYGWIN)
  set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/CMake")
else()
  set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/lib/CMake/Odil")
endif()

# https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
# https://cliutils.gitlab.io/modern-cmake/

install(EXPORT OdilTargets DESTINATION "${INSTALL_CMAKE_DIR}")

write_basic_package_version_file(
    "OdilConfigVersion.cmake" COMPATIBILITY SameMajorVersion)
configure_file(OdilConfig.cmake.in OdilConfig.cmake @ONLY)
install(
    FILES 
        ${CMAKE_CURRENT_BINARY_DIR}/OdilConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/OdilConfigVersion.cmake
    DESTINATION "${INSTALL_CMAKE_DIR}")

export(TARGETS libodil FILE "${PROJECT_BINARY_DIR}/OdilTargets.cmake")
