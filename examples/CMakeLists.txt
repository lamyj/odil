add_definitions("-D HAVE_CONFIG_H")

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE examples *.cpp)

foreach(example_file ${examples})
    get_filename_component(example ${example_file} NAME_WE)
    add_executable(${example} ${example_file})
    target_link_libraries(${example} dcmtkpp dcmdata)
endforeach()
