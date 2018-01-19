file(GLOB_RECURSE module_files *.py)
set(python_files ${module_files} odil)
add_custom_target(
    PythonFiles ${CMAKE_COMMAND} -E echo "Python files" SOURCES ${python_files})
set_target_properties(PythonFiles PROPERTIES FOLDER "Examples")

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "from distutils import sysconfig; print( sysconfig.get_python_lib( plat_specific=True, prefix='${CMAKE_INSTALL_PREFIX}' ) )"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(FILES ${module_files} DESTINATION "${PYTHON_SITE_PACKAGES}/odil/cli")
install(PROGRAMS odil DESTINATION bin)
