find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src ${JsonCpp_INCLUDE_DIRS})
add_definitions(
    ${DCMTK_DEFINITIONS}
    -D BOOST_ASIO_DYN_LINK
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
)

file(GLOB_RECURSE examples *.cpp)

foreach(example_file ${examples})
    get_filename_component(example ${example_file} NAME_WE)
    add_executable(${example} ${example_file})
    target_link_libraries(${example} odil)
endforeach()
