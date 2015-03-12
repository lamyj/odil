add_definitions("-D HAVE_CONFIG_H")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(find find.cpp)
target_link_libraries(find dcmtkpp dcmdata)
