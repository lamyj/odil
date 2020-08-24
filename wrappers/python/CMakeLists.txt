find_package(JsonCpp REQUIRED)
find_package(pybind11 REQUIRED)

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")
set(Python_Files "__init__.py")

list(SORT Header_Files)
list(SORT Source_Files)
list(SORT Python_Files)

pybind11_add_module(
    pyodil SHARED ${Source_Files} ${Header_Files} ${Python_Files})

target_compile_definitions(
    pyodil PUBLIC $<$<BOOL:BUILD_SHARED_LIBS>:BOOST_ALL_DYN_LINK>)

target_include_directories(
    pyodil 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

target_link_libraries(pyodil PUBLIC ${JsonCpp_LIBRARIES} libodil)

set_target_properties(
    pyodil PROPERTIES 
    OUTPUT_NAME _odil 
    FOLDER "Wrappers"
    $<$<PLATFORM_ID:Darwin>:SUFFIX .so>)

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "from distutils.sysconfig import *; print(get_python_lib(True, prefix='').replace('\\\\', '/'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(TARGETS pyodil DESTINATION "${PYTHON_SITE_PACKAGES}/odil")
