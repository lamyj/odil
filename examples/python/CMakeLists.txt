file(GLOB_RECURSE examples *.py)
add_custom_target(
    PythonExamples
    ${CMAKE_COMMAND} -E echo "Python examples"
    SOURCES ${examples})
set_target_properties(PythonExamples PROPERTIES FOLDER "Examples")
