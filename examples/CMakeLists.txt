find_package(Boost REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS})
add_definitions(
    ${DCMTK_DEFINITIONS}
    -D BOOST_ASIO_DYN_LINK
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
)
link_directories(${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})

file(GLOB_RECURSE examples *.cpp)

option(INSTALL_EXAMPLES "Install the examples" OFF)

foreach(example_file ${examples})
    get_filename_component(example ${example_file} NAME_WE)
    add_executable(${example} ${example_file})
    target_link_libraries(${example} libodil)
    if(INSTALL_EXAMPLES)
        install(TARGETS ${example} RUNTIME DESTINATION bin)
    endif()
    set_target_properties(${example} PROPERTIES FOLDER "Examples")
endforeach()

file(GLOB_RECURSE python_examples *.py)
add_custom_target(
    PythonExamples
    ${CMAKE_COMMAND} -E echo "Python examples"
    SOURCES ${python_examples})
set_target_properties(PythonExamples PROPERTIES FOLDER "Examples")
