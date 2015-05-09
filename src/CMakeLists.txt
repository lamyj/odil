file(GLOB_RECURSE files "*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions("-D HAVE_CONFIG_H")

add_library(dcmtkpp SHARED ${files})

target_link_libraries(dcmtkpp dcmnet dcmdata oflog ofstd pthread z)

find_library(USE_WRAP wrap)
if(USE_WRAP)
    target_link_libraries(dcmtkpp wrap)
endif()
