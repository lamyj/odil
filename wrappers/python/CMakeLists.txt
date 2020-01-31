find_package(JsonCpp REQUIRED)
find_package(pybind11 REQUIRED)

if(BUILD_SHARED_LIBS)
    add_definitions(-D BOOST_ALL_DYN_LINK)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")
set(Python_Files "__init__.py")

list(SORT Header_Files)
list(SORT Source_Files)
list(SORT Python_Files)

pybind11_add_module(pyodil SHARED ${Source_Files} ${Header_Files})

set_target_properties(pyodil PROPERTIES OUTPUT_NAME _odil FOLDER "Wrappers")
if(APPLE)
    set_target_properties(pyodil PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(pyodil ${JsonCpp_LIBRARIES} libodil)

add_custom_target(
    pyodil-pure ${CMAKE_COMMAND} -E echo "Pure-python files"
    SOURCES ${Python_Files})
set_target_properties(pyodil-pure PROPERTIES FOLDER "Wrappers")

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "from distutils.sysconfig import *; print(get_python_lib(True, prefix='').replace('\\\\', '/'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(DIRECTORY DESTINATION "${PYTHON_SITE_PACKAGES}")
install(TARGETS pyodil DESTINATION "${PYTHON_SITE_PACKAGES}/odil")
install(FILES ${Python_Files} DESTINATION "${PYTHON_SITE_PACKAGES}/odil")
