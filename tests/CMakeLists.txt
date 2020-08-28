find_package(
    Boost COMPONENTS exception filesystem log unit_test_framework REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)

add_subdirectory(tools)

file(GLOB headers *.h)
file(GLOB_RECURSE tests code/*.cpp)
if(NOT WITH_DCMTK)
    list(
        REMOVE_ITEM tests
        ${CMAKE_CURRENT_SOURCE_DIR}/code/conversion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code/DcmtkException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code/ElementAccessor.cpp)
    set(
        extra_files
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/conversion.cpp
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/ElementAccessor.cpp
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/ElementTraits.cpp
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/Exception.cpp)
endif()

foreach(test_file ${tests})
    get_filename_component(unit ${test_file} NAME_WE)
    get_filename_component(module ${test_file} PATH)
    get_filename_component(module ${module} NAME)
    if(NOT "${module}" STREQUAL "code")
        set(test "${module}_${unit}")
    else()
        set(test "${unit}")
    endif()

    add_executable(test_${test} ${test_file} ${headers} ${extra_files})
    
    target_compile_definitions(
        test_${test} 
        PRIVATE
            BOOST_ASIO_SEPARATE_COMPILATION ${DCMTK_DEFINITIONS}
            ODIL_VERSION_MAJOR=${Odil_VERSION_MAJOR}
            $<$<BOOL:BUILD_SHARED_LIBS>:BOOST_ALL_DYN_LINK>)
    
    target_include_directories(
        test_${test} PRIVATE ${CMAKE_SOURCE_DIR}/src ${DCMTK_INCLUDE_DIRS})
    
    target_link_directories(test_${test} PRIVATE ${DCMTK_LIBRARY_DIRS})
    
    target_link_libraries(
        test_${test} 
        PRIVATE 
            Boost::unit_test_framework ${DCMTK_LIBRARIES} JsonCpp::JsonCpp 
            libodil
            $<$<PLATFORM_ID:Windows>:Ws2_32>)
    
    set_target_properties(
        test_${test} PROPERTIES OUTPUT_NAME ${test} FOLDER "Tests")

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

file(GLOB_RECURSE python_tests *.py)

add_custom_target(
    PythonTests ${CMAKE_COMMAND} -E echo "Python tests" SOURCES ${python_tests})
