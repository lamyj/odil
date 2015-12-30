find_package(JsonCpp REQUIRED)

add_definitions("-D HAVE_CONFIG_H")
add_definitions("-D DCMTKPP_MAJOR_VERSION=${dcmtkpp_MAJOR_VERSION}")
add_definitions("-D BOOST_ASIO_DYN_LINK")

include_directories(${CMAKE_SOURCE_DIR}/src ${JsonCpp_INCLUDE_DIRS})

file(GLOB_RECURSE examples *.cpp)

foreach(example_file ${examples})
    get_filename_component(example ${example_file} NAME_WE)
    add_executable(${example} ${example_file})
    target_link_libraries(${example} dcmtkpp)
endforeach()
