add_definitions("-D HAVE_CONFIG_H")

include_directories(${CMAKE_SOURCE_DIR}/src)

set(examples find get store)

foreach(example ${examples})
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} dcmtkpp dcmdata)
endforeach()
