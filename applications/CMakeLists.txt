find_package(Python COMPONENTS Interpreter Development REQUIRED)

file(GLOB_RECURSE module_files *.py)
set(python_files ${module_files} odil)
add_custom_target(
    PythonFiles ${CMAKE_COMMAND} -E echo "Python files" SOURCES ${python_files})
set_target_properties(PythonFiles PROPERTIES FOLDER "Examples")

if(BUILD_PYTHON_WRAPPERS)
    execute_process(
        COMMAND ${Python_EXECUTABLE}
            -c "import os; import sysconfig; \
                scheme = {'posix': 'posix_prefix', 'nt': 'nt'}[os.name]; \
                path = sysconfig.get_path('purelib', scheme, {'base': '.'}); \
                print(path.replace(os.path.sep, '/'))"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    install(DIRECTORY DESTINATION "${PYTHON_SITE_PACKAGES}")
    install(FILES ${module_files} DESTINATION "${PYTHON_SITE_PACKAGES}/odil/cli")
    configure_file("odil" "${CMAKE_CURRENT_BINARY_DIR}/odil")
    install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/odil" DESTINATION bin)
endif()
