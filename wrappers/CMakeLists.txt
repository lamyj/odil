find_package(Boost REQUIRED COMPONENTS python)
find_package(JsonCpp REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(PythonInterp)

if(NOT "${PYTHONLIBS_VERSION_STRING}" STREQUAL "${PYTHON_VERSION_STRING}")
    message(
        FATAL_ERROR 
        "Python version mismatch: libs are ${PYTHONLIBS_VERSION_STRING} interp is ${PYTHON_VERSION_STRING}")
endif()

if(BUILD_SHARED_LIBS)
    add_definitions(-D BOOST_ALL_DYN_LINK)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src ${Boost_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE files "*.cpp")
list(SORT files)
python_add_module(pyodil SHARED ${files})
set_target_properties(
    pyodil PROPERTIES OUTPUT_NAME odil FOLDER "Wrappers")
if(APPLE)
    set_target_properties(pyodil PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(
    pyodil ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES} libodil ${PYTHON_LIBRARIES})

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "from distutils import sysconfig; print( sysconfig.get_python_lib( plat_specific=True, prefix='${CMAKE_INSTALL_PREFIX}' ) )"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(TARGETS pyodil DESTINATION ${PYTHON_SITE_PACKAGES})
