file(GLOB_RECURSE examples *.js *.html)
add_custom_target(
    JavascriptExamples
    ${CMAKE_COMMAND} -E echo "Javascript examples"
    SOURCES ${examples})
set_target_properties(JavascriptExamples PROPERTIES FOLDER "Examples")
