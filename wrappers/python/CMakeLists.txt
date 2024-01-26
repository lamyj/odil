find_package(JsonCpp REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")
set(Python_Files "__init__.py")

list(SORT Header_Files)
list(SORT Source_Files)
list(SORT Python_Files)

pybind11_add_module(pyodil SHARED ${Source_Files} ${Header_Files})

target_compile_definitions(
    pyodil PRIVATE $<$<BOOL:BUILD_SHARED_LIBS>:BOOST_ALL_DYN_LINK>)

target_include_directories(
    pyodil 
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src> ${PYTHON_INCLUDE_DIRS})

target_link_libraries(pyodil PRIVATE JsonCpp::JsonCpp libodil)

set_target_properties(
    pyodil PROPERTIES 
    OUTPUT_NAME _odil 
    FOLDER "Wrappers"
    $<$<PLATFORM_ID:Darwin>:SUFFIX .so>)

execute_process(
    COMMAND ${Python_EXECUTABLE}
        -c "import os; import sysconfig; \
            scheme = {'posix': 'posix_prefix', 'nt': 'nt'}[os.name]; \
            path = sysconfig.get_path('purelib', scheme, {'base': '.'}); \
            print(path.replace(os.path.sep, '/'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(TARGETS pyodil DESTINATION "${PYTHON_SITE_PACKAGES}/odil")
install(FILES ${Python_Files} DESTINATION "${PYTHON_SITE_PACKAGES}/odil")
