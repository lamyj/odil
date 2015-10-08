find_package(Boost COMPONENTS unit_test_framework REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions("-D HAVE_CONFIG_H")
add_definitions("-D DCMTKPP_MAJOR_VERSION=${dcmtkpp_MAJOR_VERSION}")

file(GLOB_RECURSE tests *.cpp)
foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)
    add_executable(${test} ${test_file})
    target_link_libraries(${test} dcmtkpp ${Boost_LIBRARIES})
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

        set(case "${vr}FromDcmtkpp")
        add_test("${test}_${case}" "${test}" "--run_test=${case}")

        set(case "${vr}ToDcmtkpp")
        add_test("${test}_${case}" "${test}" "--run_test=${case}")
    endforeach()

endforeach()
