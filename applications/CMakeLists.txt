file(GLOB_RECURSE python_files *.py)
set(python_files ${python_files} odil)
add_custom_target(
    PythonFiles ${CMAKE_COMMAND} -E echo "Python files" SOURCES ${python_files})
