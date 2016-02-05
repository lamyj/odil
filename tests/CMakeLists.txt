find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)

add_subdirectory(tools)

file(GLOB headers *.h)
file(GLOB_RECURSE tests code/*.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS})
add_definitions(
    ${DCMTK_DEFINITIONS}
    -D BOOST_ASIO_DYN_LINK
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
    -DBOOST_TEST_DYN_LINK
)
link_directories(${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})


foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)

    add_executable(test_${test} ${test_file} ${headers})
    target_link_libraries(test_${test} odil ${Boost_LIBRARIES})
    set_target_properties(test_${test} PROPERTIES OUTPUT_NAME ${test})

    file(READ ${test_file} content)

    set(pattern "BOOST_(AUTO|FIXTURE)_TEST_CASE\\(([^),]+)")

    string(REGEX MATCHALL ${pattern} cases ${content})

    foreach(case ${cases})
        string(REGEX REPLACE ${pattern} "\\2" case ${case})
        if(NOT ${case} MATCHES "##")
            add_test("${test}_${case}" "${test}" "--run_test=${case}")
        endif()
    endforeach()

    set(pattern "ElementTest\\([\n ]+([A-Z]+)")

    string(REGEX MATCHALL ${pattern} matches ${content})

    foreach(match ${matches})
        string(REGEX REPLACE ${pattern} "\\1" vr ${match})

        set(case "${vr}FromOdil")
        add_test("${test}_${case}" "${test}" "--run_test=${case}")

        set(case "${vr}ToOdil")
        add_test("${test}_${case}" "${test}" "--run_test=${case}")
    endforeach()

endforeach()

add_custom_target(Runner ${CMAKE_COMMAND} -E echo "Test runner" SOURCES run.sh)
